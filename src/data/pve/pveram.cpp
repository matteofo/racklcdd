#include "pveram.hpp"

PVERamReport::PVERamReport()
    : logger("PVERamReport"), command("pvesh get /cluster/resources --type node --output-format=json") {
    this->report.percent = 0;
    this->report.total = 0;
    this->report.used = 0;
}

void PVERamReport::update() {
    std::string output = this->command.run();

    auto outputJson = json::parse(output);    
    if (!outputJson.is_array()) {
        const std::string message = "Invalid JSON returned!";
        logger.error("{}", message);
        throw std::runtime_error(message);
    }

    for (auto& [_ , _value] : outputJson.items()) {
        this->report.total += _value["maxmem"].get<long>();
        this->report.used += _value["mem"].get<long>();
    }

    this->report.percent = (long)((double)((double)this->report.used / this->report.total) * 100.0);
    this->report.unitUsed = (char*) common_get_mem_unit(&(this->report.used));
    this->report.unitTot = (char*) common_get_mem_unit(&(this->report.total));
}

json PVERamReport::jsonify() {
    json j;
    
    j["type"] = 1;
    j["percent"] = this->report.percent;
    j["used"] = this->report.used;
    j["total"] = this->report.total;
    j["unitUsed"] = this->report.unitUsed;
    j["unitTot"] = this->report.unitTot;

    return j;
}

void PVERamReport::send(Serial& serial) {
    logger.log("Sending RAM report ({}{} of {}{}, {}%)",
        this->report.used, this->report.unitUsed,
        this->report.total, this->report.unitTot,
        this->report.percent
    );

    static json j = this->jsonify();
    serial.write(j.dump());
}