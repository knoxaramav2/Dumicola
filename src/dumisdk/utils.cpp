#include "utils.hpp"

static uint32_t __id_cntr = 1;

uint32_t dumisdk::nextId(){ return __id_cntr++; }

// std::string dumisdk::uuid(){ 
//     #ifdef PLATFORM_WINDOWS
//     UUID uuid;
//     U
//     #else

//     #endif
//  }