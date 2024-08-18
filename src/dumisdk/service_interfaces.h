#pragma once

#include <string>
#include "utils.h"
#include "config.h"

namespace dumisdk{

    enum ILoggerAction{
        LOG_PRINT,
        LOG_WRITE,
        LOG_PRINT_WRITE,
        LOG_DEFAULT
    };

    enum ILoggerMsgType{
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_DEBUG,
        LOG_NORMAL,
    };

    class ILogger {

        template<typename ... Args>
        OINLINE std::string __logFormat(const char* format, Args ... args) const {
            std::string ret = frmstr(format, std::forward<Args>(args)...);
            return ret;
        }

        //OINLINE virtual void __logAs(ILoggerAction action, ILoggerMsgType msgType, std::string& msg) {};
        virtual void __logAs(ILoggerAction action, ILoggerMsgType msgType, std::string& msg);

        ILoggerAction __infoPolicy = LOG_PRINT_WRITE;
        ILoggerAction __warnPolicy = LOG_PRINT_WRITE;
        ILoggerAction __errPolicy = LOG_PRINT_WRITE;
        ILoggerAction __debugPolicy = LOG_PRINT_WRITE;
        ILoggerAction __defaultPolcy = LOG_PRINT;

        public:

        template<typename ... Args>
        OINLINE inline void log_info(const char* format, Args && ... args) {
            std::string frmt = __logFormat(format, std::forward<Args>(args)...);
            __logAs(ILoggerAction::LOG_DEFAULT, ILoggerMsgType::LOG_INFO, frmt);
        }

        template<typename ... Args>
        OINLINE inline void log_warn(const char* format, Args && ... args) {
            std::string frmt = __logFormat(format, std::forward<Args>(args)...);
            __logAs(ILoggerAction::LOG_DEFAULT, ILoggerMsgType::LOG_WARN, frmt);
        }

        template<typename ... Args>
        OINLINE inline void log_error(const char* format, Args && ... args) {
            std::string frmt = __logFormat(format, std::forward<Args>(args)...);
            __logAs(ILoggerAction::LOG_DEFAULT, ILoggerMsgType::LOG_ERROR, frmt);
        }

        template<typename ... Args>
        OINLINE inline void log_debug(const char* format, Args && ... args) {
            std::string frmt = __logFormat(format, std::forward<Args>(args)...);
            __logAs(ILoggerAction::LOG_DEFAULT, ILoggerMsgType::LOG_DEBUG, frmt);
        }

//        template<typename ... Args>
//        OINLINE inline void log(ILoggerAction action, ILoggerMsgType msgType, const char* format, Args && ... args) const {
//            __logAs(action, msgType, format, __logFormat(std::forward<Args>(args)...));
//        }

        template<typename ... Args>
        OINLINE inline void log(const char* format, Args && ... args) {
            std::string frmt = __logFormat(format, std::forward<Args>(args)...);
            __logAs(ILoggerAction::LOG_DEFAULT, ILoggerMsgType::LOG_NORMAL, frmt);
        }

        virtual void setLogPolicies(
            ILoggerAction defaultPolicy=ILoggerAction::LOG_DEFAULT,
            ILoggerAction infoPolicy=ILoggerAction::LOG_DEFAULT,
            ILoggerAction debugPolicy=ILoggerAction::LOG_DEFAULT,
            ILoggerAction warnPolicy=ILoggerAction::LOG_DEFAULT,
            ILoggerAction errorPolicy=ILoggerAction::LOG_DEFAULT
        ){
            if(defaultPolicy != ILoggerAction::LOG_DEFAULT){ __defaultPolcy = defaultPolicy; }
            if(infoPolicy != ILoggerAction::LOG_DEFAULT){ __infoPolicy = infoPolicy; }
            if(debugPolicy != ILoggerAction::LOG_DEFAULT){ __debugPolicy = debugPolicy; }
            if(warnPolicy != ILoggerAction::LOG_DEFAULT){ __warnPolicy = warnPolicy; }
            if(errorPolicy != ILoggerAction::LOG_DEFAULT){ __errPolicy = errorPolicy; }
        }
    };

    class DefaultLogger: public ILogger{
        OINLINE void __logAs(ILoggerAction action, ILoggerMsgType msgType, std::string& msg){}
    };
}



