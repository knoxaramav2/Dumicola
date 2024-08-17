#include "dumicore.hpp"
#include "dumiexcept.hpp"
#include "logging.hpp"

dumicore::DumiCore* __core_inst = nullptr;

dumicore::__dcSysState::__dcSysState()
{
    active = true;
}

void dumicore::DumiCore::__runAsCncModeAuto()
{
    // while(__inst__->__state.active){

    // }
    //TODO shutdown procs
}

dumicore::DumiCore::DumiCore(){

}

dumicore::DumiCore::~DumiCore()
{
    
}

void dumicore::DumiCore::__loadServiceDefaults()
{
    //__serviceManager.registerLogger<dumisdk::DefaultLogger>();
}

void dumicore::DumiCore::start()
{
    __runAsCncModeAuto();
}

void dumicore::DumiCore::shutdown()
{
    _state.active = false;
}

int dumicore::DumiCore::checkStatus()
{

    return 0;
}

// void dumicore::DumiCore::registerServices(std::function<void(serviceman::ServiceBuilder)> func)
// {
//     func(serviceman::ServiceBuilder(__serviceManager));
// }

// serviceman::ServiceManager &dumicore::DumiCore::serviceManager()
// {
//     return __serviceManager;
// }

// std::shared_ptr<dumisdk::ILogger> dumicore::DumiCore::getLogger()
// {
//     return __serviceManager.getLogger();
// }

void dumicore::DumiCore::__init_core()
{
    if(__core_inst){ 
        //__core_inst->getLogger()->log_warn("Dumicore already initialized");
        return; 
    }

    __core_inst = new DumiCore();
    __core_inst->__loadServiceDefaults();
    __core_inst->start();
}

