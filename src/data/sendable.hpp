#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include "../serial.hpp"

using json = nlohmann::json;

class ISendable {
public:
    virtual void update() = 0;
    virtual json jsonify() = 0;
    virtual void send(Serial& serial) = 0;
};