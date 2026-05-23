#include "cputemp.hpp"

CPUTemperatureReport::CPUTemperatureReport()
	: logger("CPUTemperatureReport"), command("sensors | grep Tctl") {
	this->temp = "";
}

void CPUTemperatureReport::update() {
	std::string output = this->command.run();
	
	int pos = output.find("+");
	if (pos == std::string::npos) {
		logger.error("Failed to get temperature");
		throw std::runtime_error("Failed to get temperature");
	}

	this->temp = output.substr(pos);
	this->temp = this->temp.substr(0, this->temp.size() - 6);
	this->temp += "C";
}

json CPUTemperatureReport::jsonify() {
	json j;

	j["type"] = ReportType::PRINT;
	j["str"] = "CPU Temp: " + this->temp;

	return j;
}

void CPUTemperatureReport::send(Serial& serial) {
	logger.log("Sending CPU temperature report ({})", this->temp);
	serial.write(this->jsonify().dump());
}