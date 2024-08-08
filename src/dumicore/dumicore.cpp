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

void dumicore::DumiCore::start()
{
    if(__inst__ != nullptr){
        logerr_a("Duplicore Dumicore initialization", dumiLogger::LG_PRINTWRITE);
        return;
    }
    new dumicore::DumiCore();
    __runAsCncModeAuto();

    logmsg("DumiCore started...");
}

void dumicore::DumiCore::shutdown()
{
    __inst__->__state.active = false;

    logmsg("DumiCore shutodwn...");
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
}