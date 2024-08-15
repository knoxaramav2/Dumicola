#include "dtypes.hpp"
#include "defs.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>

dumisdk::DCMemObj::DCMemObj(DCTypes type):id(appId(this)),type(type)
{
    _value = initTypeDefault(type);
}

void *dumisdk::initTypeDefault(DCTypes type)
{
    switch (type)
    {
    case DCTypes::DCBOOL: return new DCBOOL_TYPE(getTypeDefault<DCBOOL_TYPE>());
    case DCTypes::DCINT: return new DCINT_TYPE(getTypeDefault<DCINT_TYPE>());
    case DCTypes::DCDECI: return new DCDECI_TYPE(getTypeDefault<DCDECI_TYPE>());
    case DCTypes::DCSTR: return new DCSTRING_TYPE(getTypeDefault<DCSTRING_TYPE>());
    case DCTypes::DCLIST: return new DCLIST_TYPE(getTypeDefault<DCLIST_TYPE>());
    case DCTypes::DCMAP: return new DCMAP_TYPE(getTypeDefault<DCMAP_TYPE>());
    
    default:
        break;
    }
    throw dumiexception("Illegal DC type code");
}
