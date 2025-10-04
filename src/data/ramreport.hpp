#pragma once
#include <sys/sysinfo.h>
#include "sendable.hpp"
#include "common.h"
#include "logger.hpp"

class SendableRAMReport: public ISendable {
private:
    MemUsageReport report;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    SendableRAMReport();
};