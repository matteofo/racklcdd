#include "pvestorage.hpp"

PVEStorageReport::PVEStorageReport()
    : logger("PVEStorageReport"), command("pvesh get /cluster/resources --type storage --output-format=json") {
    this->report.percent = 0;
    this->report.total = 0;
    this->report.used = 0;
}

void PVEStorageReport::update() {
    std::string output = this->command.run();

    auto outputJson = json::parse(output);    
    if (!outputJson.is_array()) {
        const std::string message = "Invalid JSON returned!";
        logger.error("{}", message);
        throw std::runtime_error(message);
    }

    for (auto& [_ , _value] : outputJson.items()) {
        this->report.total += _value["maxdisk"].get<long>();
        this->report.used += _value["disk"].get<long>();
    }

    this->report.percent = (long)((double)((double)this->report.used / this->report.total) * 100.0);
    this->report.unitUsed = (char*) common_get_mem_unit(&(this->report.used));
    this->report.unitTot = (char*) common_get_mem_unit(&(this->report.total));
}

json PVEStorageReport::jsonify() {
    json j;
    
    j["type"] = 2;
    j["percent"] = this->report.percent;
    j["used"] = this->report.used;
    j["total"] = this->report.total;
    j["unitUsed"] = this->report.unitUsed;
    j["unitTot"] = this->report.unitTot;

    return j;
}

void PVEStorageReport::send(Serial& serial) {
    logger.log("Sending Storage report ({}{} of {}{}, {}%)",
        this->report.used, this->report.unitUsed,
        this->report.total, this->report.unitTot,
        this->report.percent
    );

    static json j = this->jsonify();
    serial.write(j.dump());
}