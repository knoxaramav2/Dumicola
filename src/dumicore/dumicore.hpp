#pragma once

#include "service_interfaces.hpp"
#include "serviceman.hpp"
#include "dataman.hpp"
#include <functional>

namespace dumicore{

    struct __dcSysState{
        bool active;

        __dcSysState();
    };

    class DumiCore{

        static DumiCore* __inst__;
        __dcSysState __state;

        serviceman::ServiceManager __serviceManager;
        dumisdk::ILogger* _logger;

        static void __runAsCncModeAuto();

        DumiCore();
        ~DumiCore();

        void __cacheServices();

        public:

        static void start();
        static void shutdown();
        static int checkStatus();

        static void registerServices(std::function<void(serviceman::ServiceManager&)> func);
        static serviceman::ServiceManager& serviceManager();
        
        static std::unique_ptr<dumisdk::ILogger> getLogger();
    };
}

#define InitDumiCore dumicore::DumiCore::start();
#define Shutdown dumicore::DumiCore::shutdown();
#define RegisterServices(fnc) dumicore::DumiCore::registerServices(fnc);
//#define GetLogger(T) dynamic_cast<T*>(dumicore::DumiCore::getLogger().get())
#define GetLogger() dumicore::DumiCore::getLogger()

