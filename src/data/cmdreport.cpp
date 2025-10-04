#include "cmdreport.hpp"

void SendableCmdReport::setCommand(const std::string command) {
    this->command = command;
}

SendableCmdReport::SendableCmdReport(const std::string command) : logger("racklcdd::SendableCmdReport") {
    this->setCommand(command);
}

void SendableCmdReport::update() {
    this->output.clear();

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->command.c_str(), "r"), pclose);

    if (!pipe) {
        throw std::runtime_error(std::format("Failed to run command {}!", this->command));
    }

    static char buffer[128];

    while (std::fgets(buffer, 128, pipe.get()) != nullptr) {
        this->output += buffer;
    }
}

json SendableCmdReport::jsonify() {
    json j;

    j["type"] = 3;
    j["str"] = this->output;

    return j;
}

void SendableCmdReport::send(Serial& serial) {
    logger.log("Sending output of command {} ({})", this->command, this->output);

    static json j = this->jsonify();
    serial.write(j.dump());
}