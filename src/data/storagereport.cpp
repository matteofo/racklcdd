#include "storagereport.hpp"

void StorageReport::update() {
    std::vector<fs::path> mountPoints;
    std::ifstream procMounts("/proc/mounts");
    
    std::string line;

    // enumerate "actual" filesystems from
    while (std::getline(procMounts, line)) {
        std::stringstream stream(line);
        std::string source, mountPoint, type;

        if (stream >> source >> mountPoint >> type) {
            if (EXCLUDED_FS_TYPES.contains(type)) {
                continue;
            } else {
                logger.log("{} {} {}", source, mountPoint, type);
                mountPoints.push_back(mountPoint);
            }
        }
    }


    for (auto& point : mountPoints) {
        try {
            static const fs::space_info info = fs::space(point);
            unsigned long long cap = info.capacity;
            const char* u = common_get_mem_unit(&cap);
            logger.log("{}{}{}", point.c_str(), cap, u);
        } catch (const fs::filesystem_error& e) {
            logger.warn("{}", e.what());
        }
    }
}

json StorageReport::jsonify() {
    json j;

    j["type"] = 3;
    j["percent"] = this->report.percent;
    j["used"] = this->report.used;
    j["total"] = this->report.total;
    j["unitUsed"] = this->report.unitUsed;
    j["unitTot"] = this->report.unitTot;

    return j;
}

void StorageReport::send(Serial& serial) {
    logger.log("Sending Storage report ({}{} of {}{}, {}%)",
        this->report.used, this->report.unitUsed,
        this->report.total, this->report.unitTot,
        this->report.percent
    );

    static json j = this->jsonify();
    serial.write(j.dump());
}

StorageReport::StorageReport() : logger("racklcdd::StorageReport") {}