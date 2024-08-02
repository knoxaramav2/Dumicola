#include "__dumisdk_init.hpp"
#include "dtypes.hpp"
#include "logger.hpp"

static bool __dumicola_is_init = false;

int dumisdk::__internal::initDumicolaCommon(){
    if(__dumicola_is_init){ return 0 ;}

    logmsg("Init Dumicola commons");

    __init_standard_types();

    return 0;
}

void dumisdk::__internal::__init_standard_types(){
    
}