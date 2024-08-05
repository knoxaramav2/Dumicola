#include<stdio.h>
#include "dumiLogger.hpp"

dumiLogger::Logger* dumiLogger::Logger::__inst = nullptr;
bool dumiLogger::Logger::__color = false;
unsigned dumiLogger::Logger::__bufferSize = 10;
std::vector<std::string> dumiLogger::Logger::__logBuff;

inline void dumiLogger::Logger::__ensureLogger()
{
    if(__inst == nullptr){
        __inst = new Logger();
        logwrn("Using default logger");
    }
}

dumiLogger::Logger::Logger(unsigned _bfSize, bool _color){
    __bufferSize = _bfSize;
    __color = _color;
}

void dumiLogger::Logger::initLogger(unsigned bufferSize=10, bool color=false)
{
    if(__inst != nullptr){
        logwrn_a("Ignoring duplication logger instantiation", LG_PRINT);
        return;
    }

    __inst = new Logger(bufferSize, color);
}

#define __LG_CLR_ERR        "\x1b[31m"
#define __LG_CLR_WRN        "\x1b[33m"
#define __LG_CLR_RESET      "\x1b[0m"

void dumiLogger::Logger::log(std::string msg, LogLevel level, LoggerAction action)
{
    __ensureLogger();
    auto e_msg = level == LG_ERR ? "ERR: " : level == LG_WARN ? "WRN: " : "";
    std::string f_msg = e_msg + msg;

    auto color = 
        __color?
            level == LG_ERR ? __LG_CLR_ERR :
            level == LG_WARN ? __LG_CLR_WRN : 
            __LG_CLR_RESET
        : "";

    if(action&LG_PRINT){
        if(__color){
            printf("%s%s%s\n", color, f_msg.c_str(), __LG_CLR_RESET);
        } else{
            printf("%s\n", f_msg.c_str());
        }
    }
    if(action&LG_WRITE){
        __logBuff.push_back(f_msg);

        if(__logBuff.size() >= __bufferSize){
            logflush();
        }
    }
}

void dumiLogger::Logger::flush()
{
    __ensureLogger();
    //TODO

    __logBuff.clear();
}

template <typename... Args>
inline std::string dumiLogger::Logger::formatstr(const char *f_str, Args... args)
{
    return std::string();
}