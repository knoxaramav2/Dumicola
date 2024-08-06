#include "dumicore.hpp"
#include "dumiexcept.hpp"

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
        return;
    }
    new dumicore::DumiCore();
    __runAsCncModeAuto();
}

void dumicore::DumiCore::shutdown()
{
    __inst__->__state.active = false;
}

int dumicore::DumiCore::checkStatus()
{
    if(__inst__ == nullptr){
        return -1;
    }

    return 0;
}