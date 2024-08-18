#pragma once

#include "service_interfaces.h"
#include "serviceman.h"
#include "dataman.h"
#include <functional>

namespace dumicore{

    

    // struct __dcSysState{
    //     bool active;

    //     __dcSysState();
    // };

    class DumiCore{

        //__dcSysState _state;

        //dataman::DataManager _dataManager;
        serviceman::ServiceManager _serviceManager;

        void __runAsCncModeAuto();

        DumiCore();
        ~DumiCore();

        void __loadServiceDefaults();

        public:

        void start();
        void shutdown();
        int checkStatus();

        //void registerServices(std::function<void(serviceman::ServiceBuilder)> func);
        //serviceman::ServiceManager& serviceManager();
        
        //std::shared_ptr<dumisdk::ILogger> getLogger();

        static void __init_core();
    };

    static DumiCore* __core_inst;
}

#define InitDumiCore dumicore::DumiCore::__init_core();
#define Shutdown dumicore::__core_inst->shutdown();
//#define RegisterServices(fnc) dumicore::__core_inst->registerServices(fnc);
//#define GetLogger() dumicore::__core_inst->getLogger()

