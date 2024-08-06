#pragma once

#include "serviceman.hpp"
#include "dataman.hpp"

namespace dumicore{
    
    struct __dcSysState{
        bool active;

        __dcSysState();
    };

    class DumiCore{

        static DumiCore* __inst__;
        __dcSysState __state;

        static void __runAsCncModeAuto();

        DumiCore();
        ~DumiCore();

        public:

        static void start();
        static void shutdown();
    };
}

#define InitDumiCore dumicore::DumiCore::start();

