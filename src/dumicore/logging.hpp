#pragma once
#include "dumiLogger.hpp"

static dumiLogger::Logger __logger;

#ifdef DCCORE_NO_LOGGING
    // #define logmsg(msg)
    // #define logmsg_a(msg, action)
    // #define logwrn(msg)
    // #define logwrn_a(msg, action)
    // #define logerr(msg)
    // #define logerr_a(msg, action)
    // #define logflush()
#else
    #define logmsg(msg) __logger.log(msg, dumiLogger::LG_INFO, dumiLogger::LG_PRINT)
    // #define logmsg_a(msg, action) dumiLogger::Logger::log(msg, dumiLogger::LG_INFO, action)
    // #define logwrn(msg) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), dumiLogger::LG_WARN, dumiLogger::LG_PRINT)
    //#define logwrn_a(msg, action) __logger.log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), dumiLogger::LG_WARN, action)
    // #define logerr(msg) dumiLogger::Logger::log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), dumiLogger::LG_ERR, LG_PRINT)
    #define logerr_a(msg, action) __logger.log(frmstr("%s\n(%s : %d)", msg, __FILE__, __LINE__), dumiLogger::LG_ERR, action)
    // #define logflush() dumiLogger::Logger::flush()
#endif
