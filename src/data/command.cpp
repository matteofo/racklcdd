#include "command.hpp"

Command::Command(const std::string command) {
    this->command.assign(command);
}

const std::string Command::run() {
    this->output.clear();

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->command.c_str(), "r"), pclose);

    if (!pipe) {
        throw std::runtime_error(std::format("Failed to run command {}!", this->command));
    }

    char buffer[128];

    while (std::fgets(buffer, 128, pipe.get()) != nullptr) {
        this->output += buffer;
    }

    int end = this->output.size() - 1;

    if (this->output[end] == '\n') {
        this->output[end] = '\0';
    }

    return this->output;
}

const std::string Command::get() {
    return this->command;
}

const std::string Command::getOutput() {
    return this->output;
}