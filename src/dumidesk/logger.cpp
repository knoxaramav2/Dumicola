#include "logger.hpp"

void DesktopLogger::__logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg) {
    printf("%s\n", msg.c_str());
}

DesktopLogger::DesktopLogger(){
    printf("Desktop Logger Init\n");
}