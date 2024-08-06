#include "dumicore.hpp"
#include <stdio.h>

int main(){

    InitDumiCore
    
    auto status = dumicore::DumiCore::checkStatus();

    printf("CORE STATE: %s\n", status == 0 ? "OK" : "ERR");

    return status != 0;
}