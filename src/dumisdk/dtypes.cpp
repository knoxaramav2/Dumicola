#include "dtypes.hpp"
#include "utils.hpp"
#include "dumiexcept.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>
#include <format>

dumisdk::DCMemObj::DCMemObj(DumiBaseType t_base, DumiExtType t_ext)
{
    this->id = addrId(*this);
    this->type = SET_DTYPE_EXT(t_base, t_ext);
}

template <typename T>
inline dumisdk::DCType<T>::DCType(DumiBaseType t_base, DumiExtType t_ext, T initialValue)
    :DCMemObj(t_base, t_ext)
{
    this->__value = new T(initialValue);
}

template <typename T>
dumisdk::DCType<T>::~DCType()
{
    delete __value;
}

/**
 * DC Literal
 */

template <typename T>
dumisdk::DCLiteral<T>::DCLiteral(DumiBaseType t_base, DumiExtType t_ext, T initialValue)
    :DCType<T>(t_base, t_ext, initialValue) {}

template <typename T>
inline T dumisdk::DCLiteral<T>::get()
{
    return *this->__value;
}

template <typename T>
void dumisdk::DCLiteral<T>::set(T value)
{
    *this->__value = value;
}

/**
 * DC Collection
 */
template <typename T, typename I>
inline dumisdk::DCCollection<T, I>::DCCollection(DumiBaseType t_base, DumiExtType t_ext, T initialValue)
    :DCType<T>(t_base, t_ext, initialValue) {}

/** 
 * Type definitions 
 **/
dumisdk::DCBoolean::DCBoolean()
    :DCLiteral<bool>(DumiBaseType::BOOL, DumiExtType::BASIC_DTYPE, false)
    {}

dumisdk::DCInteger::DCInteger()
    :DCLiteral<int32_t>(DumiBaseType::INTEGER, DumiExtType::BASIC_DTYPE, 0)
    {}

dumisdk::DCDecimal::DCDecimal()
    :DCLiteral<double>(DumiBaseType::DECIMAL, DumiExtType::BASIC_DTYPE, 0.0f)
    {}

dumisdk::DCString::DCString()
    :DCLiteral<std::string>(DumiBaseType::STRING, DumiExtType::BASIC_DTYPE, "")
    {}


/* DC Map */
dumisdk::DCMap::DCMap()
    :DCCollection<std::map<APPSID, dumisdk::DCMemObj*>, APPSID>
    (DumiBaseType::MAP, DumiExtType::BASIC_DTYPE, {})
    {}

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

bool dumisdk::DCMap::remove(DCMemObj *item)
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
    :DCCollection<std::vector<DCMemObj*>, size_t>
    (DumiBaseType::LIST, DumiExtType::BASIC_DTYPE, {}){}

dumisdk::DCMemObj *dumisdk::DCList::operator[](size_t index)
{
    if(index < 0 || index >= __value->size()) { return nullptr; }
    return (*__value)[index];
}

void dumisdk::DCList::push_back(DCMemObj *item)
{
    __value->push_back(item);
}

bool dumisdk::DCList::remove(size_t index)
{
    if(index < 0 || index >= __value->size()){ return false; }
    __value->erase(__value->begin()+index);
    return true;
}

bool dumisdk::DCList::remove(DCMemObj *item)
{
    for(auto i = __value->begin(); i != __value->end(); ++i){
        if(*i == item){
            __value->erase(i);
            return true;
        }
    }
    return false;
}


/* Type Management */
dumisdk::TypeTemplate::TypeTemplate(std::string name, __type_builder builder,
DumiBaseType base, DumiExtType ext)
    :dumisdk::DCMemObj(base, ext)
{
    this->name = name;
    this->__builder = builder;
}

static dumisdk::TypeTemplateFactory* __ttf_inst = nullptr;

dumisdk::TypeTemplateFactory::TypeTemplateFactory(){
    if(__ttf_inst != nullptr){
        throw dumiexception(std::format("Duplicate instantiation of {}", NAMEOF(TypeTemplateFactory)).c_str());
    }

    __ttf_inst = this;
}

dumisdk::TypeTemplateFactory::~TypeTemplateFactory(){
    if(__ttf_inst != nullptr){
        __ttf_inst = nullptr;
    } else {

    }
}

dumisdk::TypeTemplateFactory* dumisdk::TypeTemplateFactory::getInstance(){
    if(__ttf_inst == nullptr){
        __ttf_inst = new TypeTemplateFactory();
    }
    return __ttf_inst;
}

bool dumisdk::TypeTemplateFactory::registerTemplate(){
    return false;
}


/* DC Data Manager */
dumisdk::DCDataManager::DCDataManager(){

}

dumisdk::DCDataManager::~DCDataManager(){

}

dumisdk::DCMemObj *dumisdk::DCDataManager::createVar(DumiBaseType type, DumiExtType ext)
{
    return nullptr;
}

dumisdk::DCMemObj *dumisdk::DCDataManager::requestVar(APPSID id)
{
    return __dTypeStorage.contains(id) ? 
        __dTypeStorage[id] : nullptr;
}

bool dumisdk::DCDataManager::deleteVar(APPSID id)
{
    if(__dTypeStorage.contains(id)){
        __dTypeStorage.erase(id);
        return true;
    }
    return false;
}

