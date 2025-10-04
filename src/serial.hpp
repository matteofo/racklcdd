#pragma once
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "../logger.hpp"

// wraps around UNIX serial stuff
class Serial {
private:
    int fileHandle;
    termios tty;
    bool isOpen = false;
    Logger logger;
public:
    void open(std::string deviceName);
    void write(std::string buffer);
    void close();

    Serial();
    Serial(std::string deviceName);
    ~Serial();
};