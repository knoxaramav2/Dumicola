#pragma once

#include <string>
#include <vector>
#include <format>

namespace dumisdk
{
    enum LoggerAction{
        LG_PRINT=1, LG_WRITE, LG_PRINTWRITE
    };

    enum LogLevel{
        LG_WARN, LG_ERR, LG_INFO
    };

    class Logger{
        static void initLogger(unsigned bufferSize, bool color);
        static void log(std::string msg, LogLevel level, LoggerAction action);
        static void flush();
        private:
        static inline void __ensureLogger();
        Logger(unsigned _bfSize=10, bool _color=false);
        static std::vector<std::string> __logBuff;
        static unsigned __bufferSize;
        static bool __color;
        static Logger* __inst;
    };

    #define logmsg(msg) Logger::log(std::format("{}", msg), LG_INFO, LG_PRINT)
    #define logmsg_a(msg, action) Logger::log(std::format("{}", msg), LG_INFO, action)
    #define logwrn(msg) Logger::log(std::format("{}\n({} : {})", msg, __FILE__, __LINE__), LG_WARN, LG_PRINT)
    #define logwrn_a(msg, action) Logger::log(std::format("{}\n({} : {})", msg, __FILE__, __LINE__), LG_WARN, action)
    #define logerr(msg) Logger::log(std::format("{}\n({} : {})", msg, __FILE__, __LINE__), LG_ERR, LG_PRINT)
    #define logerr_a(msg, action) Logger::log(std::format("{}\n({} : {})", msg, __FILE__, __LINE__), LG_ERR, action)
    #define logflush() Logger::flush();
}



