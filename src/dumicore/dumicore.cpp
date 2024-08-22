#include "dumicore.h"
#include "dumiexcept.h"
#include "logging.h"

dumicore::DumiCore* __core_inst = nullptr;

dumicore::__dcSysState::__dcSysState()
{
    active = false;
}

dumicore::__dcSysState::~__dcSysState()
{
}

void dumicore::DumiCore::_runAsCncModeAuto()
{
    _state.active = true;
    // while(__inst__->__state.active){

    // }
    //TODO shutdown procs
}

dumicore::DumiCore::DumiCore(){

}

dumicore::DumiCore::~DumiCore()
{
    
}

void dumicore::DumiCore::_loadServiceDefaults()
{
    //__serviceManager.registerLogger<dumisdk::DefaultLogger>();
}

void dumicore::DumiCore::_loadCoreTypes()
{
    _dataManager.registerType<dumisdk::DCBoolean>(0);
    _dataManager.registerType<dumisdk::DCInteger>(0);
    _dataManager.registerType<dumisdk::DCDecimal>(0);
    _dataManager.registerType<dumisdk::DCString>(0);
    _dataManager.registerType<dumisdk::DCList>(0);
    _dataManager.registerType<dumisdk::DCMap>(0);
}

void dumicore::DumiCore::start()
{
    _runAsCncModeAuto();
}

void dumicore::DumiCore::shutdown()
{
    //Segfault on desk
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
    __core_inst->_loadServiceDefaults();
    __core_inst->_loadCoreTypes();
    __core_inst->start();
}

void dumicore::DumiCore::__destroy_core()
{
    if(!__core_inst){return;}
    __core_inst->shutdown();
    delete __core_inst;
}
