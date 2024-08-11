//
// Created by knox on 8/10/24.
//

#include "mobileLogger.h"

void AndroidLogger::__logAs(dumisdk::ILoggerAction action, dumisdk::ILoggerMsgType msgType, std::string& msg) {
    android_LogPriority logtype;
    switch (msgType) {
        case dumisdk::ILoggerMsgType::LOG_DEBUG:
            logtype=ANDROID_LOG_DEBUG; break;
        case dumisdk::ILoggerMsgType::LOG_WARN:
            logtype=ANDROID_LOG_WARN; break;
        case dumisdk::ILoggerMsgType::LOG_ERROR:
            logtype=ANDROID_LOG_ERROR; break;
        case dumisdk::ILoggerMsgType::LOG_INFO:
            logtype=ANDROID_LOG_INFO; break;
        default:
            logtype=ANDROID_LOG_DEFAULT; break;
    }

    __android_log_print(logtype, "DUMICOLA", "%s", msg.c_str());
}