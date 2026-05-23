#include "common.h"

const char* common_get_mem_unit(unsigned long long* mem) {
    static const char* MEM_UNITS[] = {"B", "K", "M", "G", "T", "P", "?"};

    if (mem == 0) { return MEM_UNITS[0]; }
    if (*mem > 1e+15) { return MEM_UNITS[6]; } // check if we're past the PB mark

    int i = 0;

    while (*mem > 1000) {
        *mem /= 1000;
        i++;
    }

    return MEM_UNITS[i];
}