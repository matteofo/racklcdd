#pragma once

enum ReportType {
    CPU_USAGE,
    RAM_USAGE,
    STORAGE_USAGE,
    PRINT
};

struct CPUUsageReport {
    int percent;
    int cores;
};

struct MemUsageReport {
    int percent;
    unsigned long long used;
    unsigned long long total;
    char *unitUsed;
    char *unitTot;
};

// reduces mem to lowest whole memory unit and returns unit character
const char* common_get_mem_unit(unsigned long long* mem);