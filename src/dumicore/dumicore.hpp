#pragma once

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

        static void __runAsCncModeAuto();

        DumiCore();
        ~DumiCore();

        public:

        static void start();
        static void shutdown();
        static int checkStatus();

        static void registerServices(std::function<void(serviceman::ServiceManager&)> func);
    };
}

#define InitDumiCore dumicore::DumiCore::start();
#define Shutdown dumicore::DumiCore::shutdown();
#define RegisterServices(fnc) dumicore::DumiCore::registerServices(fnc);

