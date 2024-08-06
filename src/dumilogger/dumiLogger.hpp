#pragma once

#include <string>
#include <vector>
#include "dc_string.hpp"

namespace dumiLogger
{
    enum LoggerAction{
        LG_PRINT=1, LG_WRITE, LG_PRINTWRITE
    };

    enum LogLevel{
        LG_WARN, LG_ERR, LG_INFO
    };

    class Logger{
        static inline void __ensureLogger();
        Logger(unsigned _bfSize=10, bool _color=false);
        static std::vector<std::string> __logBuff;
        static unsigned __bufferSize;
        static bool __color;
        static Logger* __inst;
        public:
        static void initLogger(unsigned bufferSize, bool color);
        static void log(std::string msg, LogLevel level, LoggerAction action);
        static void flush();      
    };
}

#define logmsg(msg) dumiLogger::Logger::log(msg, LG_INFO, LG_PRINT)
#define logmsg_a(msg, action) dumiLogger::Logger::log(msg, LG_INFO, action)
#define logwrn(msg) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), LG_WARN, LG_PRINT)
#define logwrn_a(msg, action) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), LG_WARN, action)
#define logerr(msg) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), LG_ERR, LG_PRINT)
#define logerr_a(msg, action) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), LG_ERR, action)
#define logflush() dumiLogger::Logger::flush()
