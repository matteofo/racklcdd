#pragma once
#include "sendable.hpp"
#include "command.hpp"
#include "common.h"

class PVERamReport: public ISendable {
private:
    Command command;
    MemUsageReport report;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    PVERamReport();
};