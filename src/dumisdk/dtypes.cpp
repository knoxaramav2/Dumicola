#include "dtypes.hpp"
#include "utils.hpp"
#include "dumiexcept.hpp"
#include "logger.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>
#include <format>

dumisdk::DCMemObj::DCMemObj(std::string name)
{
    this->id = addrId(*this);
    this->hashId = FNV1A(name);
}

template <typename T>
inline dumisdk::DCType<T>::DCType(std::string name, T initialValue)
    :DCMemObj(name)
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
dumisdk::DCLiteral<T>::DCLiteral(std::string name, T initialValue)
    :DCType<T>(name, initialValue) {}

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
inline dumisdk::DCCollection<T, I>::DCCollection(std::string name, T initialValue)
    :DCType<T>(name, initialValue) {}

/** 
 * Type definitions 
 **/
dumisdk::DCBoolean::DCBoolean()
    :DCLiteral<bool>(DC_BOOL, false)
    {}

dumisdk::DCInteger::DCInteger()
    :DCLiteral<int32_t>(DC_INTEGER, 0)
    {}

dumisdk::DCDecimal::DCDecimal()
    :DCLiteral<double>(DC_DECIMAL, 0.0f)
    {}

dumisdk::DCString::DCString()
    :DCLiteral<std::string>(DC_STIRNG, "")
    {}


/* DC Map */
dumisdk::DCMap::DCMap()
   : DCCollection<std::map<APPSID, DCMemObj*>, APPSID>(DC_MAP, {}) {}

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
    : DCCollection<std::vector<DCMemObj*>, size_t>(DC_LIST, {}) {}

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
dumisdk::TypeTemplate::TypeTemplate(std::string name, __type_builder builder)
    :dumisdk::DCMemObj(name)
{
    this->name = name;
    this->__builder = builder;
}

dumisdk::DCMemObj *dumisdk::TypeTemplate::build()
{
    return nullptr;
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

        for(auto i: __ttf_inst->__templates){
            delete  i.second;
        }

        __ttf_inst = nullptr;
    } else {
        logerr_a(std::format("{} deconstructed with invalid static instance", NAMEOF(TypeTemplateFactory)), LoggerAction::LG_PRINTWRITE);
    }
}

dumisdk::TypeTemplateFactory* dumisdk::TypeTemplateFactory::getInstance(){
    if(__ttf_inst == nullptr){
        __ttf_inst = new TypeTemplateFactory();
    }
    return __ttf_inst;
}

bool dumisdk::TypeTemplateFactory::registerTemplate(std::string name, __type_builder builder){

    HASHID hash = FNV1A(name);

    for(auto i:__ttf_inst->__templates){
        if(i.first==hash){ 
            logerr_a(std::format("Duplicate type name: {}", name), LoggerAction::LG_PRINTWRITE);
            return false; 
        }
    }

    TypeTemplate* newTmpl = new TypeTemplate(name, builder);
    __templates[appId(newTmpl)] = newTmpl;

    return true;
}

// dumisdk::DCMemObj *dumisdk::TypeTemplateFactory::instanceOf(std::string name)
// {
//     return instanceOf(FNV1A(name));
// }

// dumisdk::DCMemObj *dumisdk::TypeTemplateFactory::instanceOf(HASHID id)
// {
//     if(__templates.contains(id)){
//         return __templates[id]->build();
//     }
//     return nullptr;
// }

/* DC Data Manager */
dumisdk::DCDataManager::DCDataManager(){
    __factory = TypeTemplateFactory::getInstance();
}

dumisdk::DCDataManager::~DCDataManager(){

}

dumisdk::DCMemObj *dumisdk::DCDataManager::createVar(std::string name)
{
    HASHID hash = FNV1A(name);
    if(__dTypeStorage.contains(hash)){
        //return __factory->instanceOf(hash);
    }
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

