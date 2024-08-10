#include "dtypes.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>

dumisdk::DCMemObj::DCMemObj(std::string name)
{
    this->id = addrId(*this);
    this->hashId = FNV1A(name);
}
