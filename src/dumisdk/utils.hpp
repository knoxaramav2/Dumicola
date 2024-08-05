#pragma once
#include "defs.hpp"
#include <string>

namespace dumisdk{
    uint32_t nextId();
    uint32_t FNV1A(std::string);

    #define addrId(obj) reinterpret_cast<APPSID>(&obj);
}

#define NAMEOF(x) #x

