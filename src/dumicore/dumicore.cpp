#include "dumicore.hpp"
#include "dumiexcept.hpp"

dumicore::__dcSysState::__dcSysState()
{
    active = true;
}

void dumicore::DumiCore::__runAsCncModeAuto()
{
    while(__inst__->__state.active){

    }
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
    __runAsCncModeAuto();
}

void dumicore::DumiCore::shutdown()
{
    __inst__->__state.active = false;
}