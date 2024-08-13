#pragma once

#include "defs.hpp"

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace dumisdk
{
    enum DCTypes{
        DCBOOL, DCINT, DCDECI,
        DCSTR, DCMAP, DCLIST
    };
    
    typedef bool DCBOOL_TYPE;
    typedef long DCINT_TYPE;
    typedef double DCDECI_TYPE;
    typedef std::string DCSTRING_TYPE;
    template<typename T>
    using DCLIST_TYPE = std::vector<T>;
    template<typename T>
    using DCMAP_TYPE = std::map<HASHID, T>;

    
};

