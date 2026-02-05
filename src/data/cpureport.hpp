#pragma once
#include <boost/thread.hpp>
#include <sys/sysinfo.h>
#include "sendable.hpp"
#include "common.h"
#include "logger.hpp"

class CPUReport: public ISendable {
private:
    CPUUsageReport report;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    CPUReport();
};