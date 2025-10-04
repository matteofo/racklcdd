#pragma once
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>
#include <pwd.h>
#include <sys/statvfs.h>
#include "sendable.hpp"
#include "common.h"
#include "logger.hpp"

namespace fs = std::filesystem;

const std::set<std::string> EXCLUDED_FS_TYPES = {
    "proc",
    "sysfs",
    "tmpfs",
    "devtmpfs",
    "cgroup",
    "cgroup2",
    "fuse.lxcfs",
    "efivarfs",
    "securityfs",
    "devpts",
    "pstore",
    "bpf",
    "autofs",
    "debugfs",
    "hugetlbfs",
    "mqueue",
    "tracefs",
    "configfs",
    "binfmt_misc",
    "overlay",
    "nsfs",
    "fuse.gvfsd-fuse",
    "fuse.portal",
    "fusectl"
};

class SendableStorageReport: public ISendable {
private:
    MemUsageReport report;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    SendableStorageReport();
};