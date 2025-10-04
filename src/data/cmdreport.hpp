#include "sendable.hpp"

class SendableCmdReport: public ISendable {
private:
    std::string command;
    std::string output;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    void setCommand(const std::string command); 
    SendableCmdReport(const std::string command);
};