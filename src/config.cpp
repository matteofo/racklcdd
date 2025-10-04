#include "config.hpp"

std::string Config::getDevice() {
    return this->device;
}

long Config::getReportInterval() {
    return this->reportInterval;
}

void Config::loadConfig() {
    std::string realPath = std::getenv("HOME");
    realPath += CONFIG_PATH;

    logger.log("Loading config from: {}", realPath);

    std::ifstream stream(realPath);
    if (stream.fail()) {
        throw std::runtime_error("Config file not found! Expected at: ~" CONFIG_PATH);
    }

    json configJson = json::parse(stream);
    stream.close();
    if (!configJson.contains("device") || !configJson.contains("reportInterval")) {
        throw std::runtime_error("Malformed config! Expecting device and reportInterval values.");
    }

    this->device = configJson["device"];
    this->reportInterval = configJson["reportInterval"];
}

Config::Config() : logger("racklcdd::Config") {
    try {
        this->loadConfig();
    } catch (std::runtime_error& e) {
        logger.error("{}", e.what());
        std::terminate();
    }
}