#include "dtypes.hpp"
#include "utils.hpp"
#include "dumiexcept.hpp"
#include "dc_string.hpp"

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
    :DCLiteral<std::string>(DC_STRING, "")
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
dumisdk::__internal::TypeTemplate::TypeTemplate(std::string name, __type_builder builder)
    :dumisdk::DCMemObj(name)
{
    this->name = name;
    this->__builder = builder;
}

dumisdk::DCMemObj *dumisdk::__internal::TypeTemplate::build()
{
    return __builder();
}

dumisdk::__internal::TypeTemplateFactory::TypeTemplateFactory(){
    
}

dumisdk::__internal::TypeTemplateFactory::~TypeTemplateFactory(){

    for(auto i: __templates){
        delete  i.second;
    }
}

bool dumisdk::__internal::TypeTemplateFactory::registerTemplate(std::string name, __type_builder builder){

    HASHID hash = FNV1A(name);

    for(auto i:__templates){
        if(i.first==hash){ 
            //throw new std::runtime_error(frmstr("TemplateFactory: Duplicate type name %d\n", name.c_str()));
            return false; 
        }
    }

    TypeTemplate* newTmpl = new TypeTemplate(name, builder);
    __templates[hash] = newTmpl;

    return true;
}

dumisdk::DCMemObj *dumisdk::__internal::TypeTemplateFactory::instanceOf(std::string name)
{
    return instanceOf(FNV1A(name));
}

dumisdk::DCMemObj *dumisdk::__internal::TypeTemplateFactory::instanceOf(HASHID id)
{
    if(__templates.contains(id)){
        auto inst = __templates[id]->build();
        return inst;
    }
    return nullptr;
}

bool dumisdk::__internal::TypeTemplateFactory::hasType(std::string name)
{
    return hasType(hashId(name));
}

bool dumisdk::__internal::TypeTemplateFactory::hasType(HASHID id)
{
    return __templates.contains(id);
}

/* DC Data Manager */
dumisdk::__internal::DCDataManager::DCDataManager(bool loadDefaults){
    __factory = new TypeTemplateFactory();
    if(loadDefaults){ loadDefaultTypes(); }
}

dumisdk::__internal::DCDataManager::~DCDataManager(){
    delete __factory;
}

APPSID dumisdk::__internal::DCDataManager::createVar(std::string typeName)
{
    return createVar(hashId(typeName));
}

APPSID dumisdk::__internal::DCDataManager::createVar(HASHID typeId)
{
    bool hasType = __factory->hasType(typeId);
    static uintptr_t utest = 0;

    if(__factory->hasType(typeId)){
        auto typeInst = __factory->instanceOf(typeId);
        auto instId = appId(typeInst);
        utest = instId;
        __dTypeStorage[instId] = typeInst;
        return instId;
    }
    return 0;
}

dumisdk::DCMemObj *dumisdk::__internal::DCDataManager::requestVar(APPSID id)
{
    if(__dTypeStorage.contains(id)){
        return __dTypeStorage[id];
    } else {
        return nullptr;
    }

    return __dTypeStorage.contains(id) ? 
        __dTypeStorage[id] : nullptr;
}

bool dumisdk::__internal::DCDataManager::deleteVar(APPSID id)
{
    if(__dTypeStorage.contains(id)){
        __dTypeStorage.erase(id);
        return true;
    }
    return false;
}

void dumisdk::__internal::DCDataManager::loadDefaultTypes(){
    auto mk_bool = [](){return (DCMemObj*)(new DCBoolean());};
    auto mk_integer = [](){return (DCMemObj*)(new DCInteger());};
    auto mk_decimal = [](){return (DCMemObj*)(new DCDecimal());};
    auto mk_string = [](){return (DCMemObj*)(new DCString());};
    auto mk_list = [](){return (DCMemObj*)(new DCList());};
    auto mk_map = [](){return (DCMemObj*)(new DCMap());};

    __factory->registerTemplate(DC_BOOL, mk_bool);
    __factory->registerTemplate(DC_INTEGER, mk_integer);
    __factory->registerTemplate(DC_DECIMAL, mk_decimal);
    __factory->registerTemplate(DC_STRING, mk_string);
    __factory->registerTemplate(DC_LIST, mk_list);
    __factory->registerTemplate(DC_MAP, mk_map);
}
