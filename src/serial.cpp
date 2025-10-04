#include "serial.hpp"

void Serial::open(std::string deviceName) {
    this->fileHandle = ::open(deviceName.c_str(), O_RDWR | O_SYNC);
    if (this->fileHandle < 0) {
        throw std::runtime_error("Opening device " + deviceName + " failed!");
    }

    if (tcgetattr(this->fileHandle, &this->tty) != 0) {
        throw std::runtime_error(std::format("tcgetattr failed with code {} ({})", errno, strerror(errno)));
    }

    // set serial parameters

    // no parity bit
    tty.c_cflag &= ~CSTOPB;
    // 8 bits per byte
    tty.c_cflag |= CS8;
    // no RTS/CTS (whatever that is)
    tty.c_cflag &= ~CRTSCTS;
    // ...more stuff
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;

    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo

    tty.c_lflag &= ~ISIG;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // baud rate: 9600 
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    if (tcsetattr(fileHandle, TCSANOW, &tty) != 0) {
        throw std::runtime_error(std::format("tcsetattr failed with code {} ({})", errno, strerror(errno)));
    }

    this->isOpen = true;
}

Serial::Serial() : logger("racklcdd::Serial") {}

Serial::Serial(std::string deviceName) : logger("racklcdd::Serial") {
    try {
        this->open(deviceName);
    } catch (std::runtime_error& e) {
        logger.error("{}", e.what());
        std::terminate();
    }
}

void Serial::write(std::string buffer) {
    ::write(this->fileHandle, buffer.c_str(), buffer.length());
    int e = tcdrain(this->fileHandle); // no buffering of serial data
}

void Serial::close() {
    if (this->isOpen) {
        ::close(this->fileHandle);
        this->isOpen = false;
    } else {
        throw std::runtime_error("Tried to close a non-open port!");
    }
}

Serial::~Serial() {
    try {
        this->close();
    } catch (std::runtime_error& e) {
        logger.warn("{}", e.what());
    }
}