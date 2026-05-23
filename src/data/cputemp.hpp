#pragma once
#include "sendable.hpp"
#include "common.h"
#include "command.hpp"
#include "logger.hpp"

class CPUTemperatureReport: public ISendable {
private:
	Command command;
	Logger logger;
	std::string temp;
public:
	void update();
    json jsonify();
    void send(Serial& serial);

    CPUTemperatureReport();
};