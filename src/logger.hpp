#pragma once
#include <iostream>
#include <print>

#define COLOR_RESET "\x1b[0m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"

class Logger {
private:
    std::string className;
    template <typename... Args>
    void _log(const std::format_string<Args...> fmt, Args &&...args) {
        std::string out = "";

        if (!this->className.empty())
            out += std::format("{}", this->className);

        out += ": ";
        out += std::format(fmt, std::forward<Args>(args)...);
        std::println("{}", out);
    }

public:
    template <typename... Args>
    void log(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("[log] ");
        this->_log(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_YELLOW);
        std::print("[warn] ");
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    template <typename... Args>
    void error(const std::format_string<Args...> fmt, Args &&...args) {
        std::print("{}", COLOR_RED);
        std::print("[error] ");
        this->_log(fmt, std::forward<Args>(args)...);
        std::print("{}", COLOR_RESET);
    }

    Logger() = default;
    Logger(std::string className) {
        this->className = className;
    }
};