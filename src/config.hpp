#pragma once

#include <iostream>
#include <print>
#include <fstream>
#include <nlohmann/json.hpp>

#include "logger.hpp"

#define CONFIG_PATH "/.config/racklcdd/config.json"

using json = nlohmann::json;

class Config {
private:
    std::string device;
    long reportInterval;
    Logger logger;
public:
    // e.g. /dev/ttyACM0
    std::string getDevice();
    // in ms
    long getReportInterval();

    void loadConfig();
    Config();
};