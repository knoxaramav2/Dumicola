#include "dtypes.hpp"
#include "defs.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>
#include <memory>

dumisdk::DCMemObj::DCMemObj(TypeId type, void* value):id(appId(this)),type(type)
{
    
}

// dumisdk::DCMemObj::~DCMemObj()
// {
    
// }
