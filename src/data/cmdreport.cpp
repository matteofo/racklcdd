#include "cmdreport.hpp"

CmdReport::CmdReport(const std::string command) : logger("racklcdd::CmdReport"), command(command) {
}

void CmdReport::update() {
    this->command.run();
}

json CmdReport::jsonify() {
    json j;

    j["type"] = 3;
    j["str"] = this->command.getOutput();

    return j;
}

void CmdReport::send(Serial& serial) {
    logger.log("Sending output of command {} ({})", this->command.get(), this->command.getOutput());

    json j = this->jsonify();
    serial.write(j.dump());
}