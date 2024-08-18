//
// Created by knox on 8/9/24.
//

#ifndef DUMIMOBILE_MOBILELOGGER_H
#define DUMIMOBILE_MOBILELOGGER_H

#include <android/log.h>
#include "service_interfaces.h"

class AndroidLogger: public dumisdk::ILogger{
    void __logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg);
};



#endif //DUMIMOBILE_MOBILELOGGER_H
