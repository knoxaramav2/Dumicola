#pragma once

#include <string>
#include <vector>
#include "dc_string.hpp"

/**
 * TODO
 * Apply logging methods based on target platform
 * Defaults:
 * Desktop:
 *  Normal
 * Mobile
 *  Include android/log.h
 *  __android_log_print(...)
 * Microcontrollers
 *  Do nothing
 *   (Custom log service?)
 */

namespace dumiLogger
{
    enum LoggerAction{
        LG_PRINT=1, LG_WRITE, LG_PRINTWRITE
    };

    enum LogLevel{
        LG_WARN, LG_ERR, LG_INFO
    };

    class Logger{
        inline void __ensureLogger();
        std::vector<std::string> __logBuff;
        unsigned __bufferSize;
        bool __color;
        Logger* __inst;
        public:
        Logger(unsigned _bfSize=10, bool _color=false);
        void initLogger(unsigned bufferSize, bool color);
        void log(std::string msg, LogLevel level, LoggerAction action);
        void flush();      
    };
}

