#include "dtypes.h"
#include "defs.h"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>
#include <memory>

dumisdk::DCMemObj::DCMemObj(TypeId type):id(appId(this)),type(type){}

dumisdk::DCMemObj::DCMemObj():id(appId(this)),type(typeId(void)){}

dumisdk::DCBoolean::DCBoolean():DCLiteral(), DCType(new DCBOOL_TYPE(false)){}

dumisdk::DCInteger::DCInteger():DCLiteral(), DCType(new DCINT_TYPE(0)){}

dumisdk::DCDecimal::DCDecimal():DCLiteral(), DCType(new DCDECI_TYPE(0.0f)){}

dumisdk::DCString::DCString():DCLiteral(), DCType(new DCSTRING_TYPE("")){}

dumisdk::DCMap::DCMap():DCCollection(new DCMAP_TYPE({})){}

dumisdk::DCList::DCList():DCCollection(new DCLIST_TYPE({})){}


