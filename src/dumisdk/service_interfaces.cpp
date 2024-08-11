#include "service_interfaces.hpp"

void dumisdk::ILogger::__logAs(ILoggerAction action, ILoggerMsgType msgType, std::string &msg)
{ 
    printf("(Def) %s\n", msg.c_str());
}
