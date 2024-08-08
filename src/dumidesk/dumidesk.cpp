#include "dumicore.hpp"
#include <stdio.h>

int main(){

    InitDumiCore
    

    RegisterServices([](serviceman::ServiceManager& sm){
        sm.registerInstance<bool>();
    });


    auto status = dumicore::DumiCore::checkStatus();

    printf("CORE STATE: %s\n", status == 0 ? "OK" : "ERR");

    Shutdown

    return status != 0;
}