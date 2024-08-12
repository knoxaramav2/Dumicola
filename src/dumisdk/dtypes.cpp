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

/** 
 * Type definitions 
 **/
dumisdk::DCBoolean::DCBoolean()
    :dumisdk::DCLiteral<bool>(DC_BOOL, false)
    {}

dumisdk::DCInteger::DCInteger()
    :dumisdk::DCLiteral<int32_t>(DC_INTEGER, 0)
    {}

dumisdk::DCDecimal::DCDecimal()
    :dumisdk::DCLiteral<double>(DC_DECIMAL, 0.0f)
    {}

dumisdk::DCString::DCString()
    :dumisdk::DCLiteral<std::string>(DC_STRING, "")
    {}

/* DC Map */
dumisdk::DCMap::DCMap()
   : dumisdk::DCCollection<std::map<APPSID, dumisdk::DCMemObj*>, APPSID>(DC_MAP, {}) {}

dumisdk::DCMemObj *dumisdk::DCMap::operator[](APPSID id)
{
    for(auto i = __value->begin(); i != __value->end(); ++i){
        if(i->second->id == id){
            return i->second;
        }
    }

    return nullptr;
}

bool dumisdk::DCMap::remove(APPSID id)
{
    return __value->erase(id) > 0;
}

bool dumisdk::DCMap::remove(dumisdk::DCMemObj *item)
{
    size_t idx = -1;
    for(auto i = __value->begin(); i != __value->end(); ++i){
        if(i->second == item){
            __value->erase(i);
            return true;
        }
    }

    return false;
}


/* DC List */
dumisdk::DCList::DCList()
    : dumisdk::DCCollection<std::vector<dumisdk::DCMemObj*>, size_t>(DC_LIST, {}) {}

dumisdk::DCMemObj *dumisdk::DCList::operator[](size_t index)
{
    if(index < 0 || index >= __value->size()) { return nullptr; }
    return (*__value)[index];
}

void dumisdk::DCList::push_back(dumisdk::DCMemObj *item)
{
    __value->push_back(item);
}

bool dumisdk::DCList::remove(size_t index)
{
    if(index < 0 || index >= __value->size()){ return false; }
    __value->erase(__value->begin()+index);
    return true;
}

bool dumisdk::DCList::remove(dumisdk::DCMemObj *item)
{
    for(auto i = __value->begin(); i != __value->end(); ++i){
        if(*i == item){
            __value->erase(i);
            return true;
        }
    }
    return false;
}