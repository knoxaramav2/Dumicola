#include "dumicore.hpp"
#include "dumiexcept.hpp"
#include "logging.hpp"

dumicore::DumiCore* dumicore::DumiCore::__inst__;

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
    if(__inst__ != nullptr){
        throw dumiexception("Duplicate instantation of Dumicore");
    }

    __inst__ = this;
}

dumicore::DumiCore::~DumiCore()
{
    
}

void dumicore::DumiCore::__cacheServices()
{
    //_logger = __serviceManager.resolveLogger().get();
}

void dumicore::DumiCore::start()
{
    new dumicore::DumiCore();
    __runAsCncModeAuto();
}

void dumicore::DumiCore::shutdown()
{
    __inst__->__state.active = false;

    //__inst__->_logger->log("DumiCore shutodwn...");
}

int dumicore::DumiCore::checkStatus()
{
    if(__inst__ == nullptr){
        return -1;
    }

    return 0;
}

void dumicore::DumiCore::registerServices(std::function<void(serviceman::ServiceManager &)> func)
{
    func(__inst__->__serviceManager);
    __inst__->__cacheServices();
}

serviceman::ServiceManager &dumicore::DumiCore::serviceManager()
{
    return __inst__->__serviceManager;
}

std::unique_ptr<dumisdk::ILogger> dumicore::DumiCore::getLogger()
{
    return __inst__->__serviceManager.resolveSingelton<dumisdk::ILogger>();
}
