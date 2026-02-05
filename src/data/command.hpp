#pragma once
#include <iostream>
#include <memory>

class Command {
private:
    std::string command;
    std::string output;
public:
    const std::string run();
    const std::string get();
    const std::string getOutput();
    Command(const std::string command);
};