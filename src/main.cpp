#include <iostream>
#include <print>

#include <chrono>
#include <thread>

#include "racklcdd.hpp"
#include "config.hpp"
#include "logger.hpp"
#include "serial.hpp"

#include "data/sendable.hpp"
#include "data/cpureport.hpp"
#include "data/ramreport.hpp"
#include "data/storagereport.hpp"
#include "data/cmdreport.hpp"
#include "data/pve/pvestorage.hpp"
#include "data/pve/pveram.hpp"

#ifndef RACKLCD_TESTING
int main() {
    Logger logger("racklcdd");
    logger.log("Starting up...");

    Config conf;
    Serial serial(conf.getDevice());

    ISendable* modes[] = {
        new CPUReport(),
        new PVERamReport(),
        new PVEStorageReport(),
        new CmdReport("uname -s -r"),
        new CmdReport("hostname -i | awk '{print $1}'")
    };

    //daemon(1, 1);

    int mode = 0;
    while (true) {
        modes[mode]->update();
        modes[mode]->send(serial);

        // wrap mode counter around size of modes
        mode = (++mode) % (sizeof(modes) / sizeof(ISendable*));

        // sleep for delay defined in config
        std::this_thread::sleep_for(std::chrono::milliseconds(conf.getReportInterval()));
    }

    return 0;
}
#endif