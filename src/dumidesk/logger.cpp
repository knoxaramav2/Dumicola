#include "logger.hpp"

void DesktopLogger::__logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg) {

    const char* prfx;
    int clr;

    switch (msgType)
    {
    case dumisdk::ILoggerMsgType::LOG_DEBUG: 
        prfx = "DEBUG |";
        clr = 95;
        break;
    case dumisdk::ILoggerMsgType::LOG_INFO: 
        prfx = "(INFO)";
        clr = 96;
     break;
    case dumisdk::ILoggerMsgType::LOG_WARN: 
        prfx = "WRN:";
        clr = 33;
     break;
    case dumisdk::ILoggerMsgType::LOG_ERROR: 
        prfx = "ERR:";
        clr = 31;
     break;
    default:
        printf("%s\n", msg.c_str());
        return;
    }

    printf("\033[%dm%s %s\033[0m\n", clr, prfx, msg.c_str());
}
