#include "ramreport.hpp"

void SendableRAMReport::update() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        throw std::runtime_error("sysinfo failed!");
    }

    this->report.total = info.totalram;
    this->report.unitTot = (char*) common_get_mem_unit(&(this->report.total));

    this->report.used = info.freeram;
    this->report.unitUsed = (char*) common_get_mem_unit(&(this->report.used));

    this->report.percent = ((double)this->report.used / (double)this->report.total) * 100;
}

json SendableRAMReport::jsonify() {
    json j;

    j["type"] = 1;
    j["percent"] = this->report.percent;
    j["used"] = this->report.used;
    j["total"] = this->report.total;
    j["unitUsed"] = this->report.unitUsed;
    j["unitTot"] = this->report.unitTot;

    return j;
}

void SendableRAMReport::send(Serial& serial) {
    logger.log("Sending RAM report ({}{} of {}{}, {}%)",
        this->report.used, this->report.unitUsed,
        this->report.total, this->report.unitTot,
        this->report.percent
    );

    json j = this->jsonify();
    serial.write(j.dump());
}

SendableRAMReport::SendableRAMReport() : logger("racklcdd::SendableRAMReport") {}