#pragma once
#include "defs.hpp"
#include <cstdint>
#include <string>

namespace dumisdk{
    uint32_t nextId();
    //std::string uuid();
    
    #define addrId(obj) reinterpret_cast<APPSID>(&obj);
}

