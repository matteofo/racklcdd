#include "sendable.hpp"
#include "command.hpp"

class CmdReport: public ISendable {
private:
    Command command;
    Logger logger;
public:
    void update();
    json jsonify();
    void send(Serial& serial);

    CmdReport(const std::string command);
};