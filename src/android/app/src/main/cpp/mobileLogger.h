//
// Created by knox on 8/9/24.
//

#ifndef DUMIMOBILE_MOBILELOGGER_H
#define DUMIMOBILE_MOBILELOGGER_H

#include <android/log.h>
#include "service_interfaces.hpp"

class DesktopLogger: public dumisdk::ILogger{
    OINLINE void __logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg) override;

public:
    const char* Title = "Mobile Logger";
};

#endif //DUMIMOBILE_MOBILELOGGER_H
