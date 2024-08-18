#pragma once

#include "service_interfaces.h"

class DesktopLogger: public dumisdk::ILogger{
    void __logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg);
};

