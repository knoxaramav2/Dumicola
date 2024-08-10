#pragma once

#include "service_interfaces.hpp"

class DesktopLogger: public dumisdk::ILogger{
    void __logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg);
    // void __logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg) {
    //     printf(">> LOG <<\n");
    // }

    public:

    DesktopLogger();

};

