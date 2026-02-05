#include "cpureport.hpp"

void CPUReport::update() {
    //this->report.cores = get_nprocs();
    this->report.cores = boost::thread::physical_concurrency();

    double loads[1];
    getloadavg(loads, 1);

    this->report.percent = (int) *loads;
}

json CPUReport::jsonify() {
    json j;

    j["type"] = 0;
    j["percent"] = this->report.percent;
    j["cores"] = this->report.cores;

    return j;
}

void CPUReport::send(Serial& serial) {
    logger.log("Sending CPU report ({}%, {} cores)", this->report.percent, this->report.cores);

    json j = this->jsonify();
    serial.write(j.dump());
}

CPUReport::CPUReport() : logger("racklcdd::CPUReport") {}