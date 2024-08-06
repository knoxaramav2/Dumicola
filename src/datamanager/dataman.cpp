#include "dataman.hpp"
#include "maputil.hpp"

/** 
 * Type definitions 
 **/
dataman::DCBoolean::DCBoolean()
    :dumisdk::DCLiteral<bool>(DC_BOOL, false)
    {}

dataman::DCInteger::DCInteger()
    :dumisdk::DCLiteral<int32_t>(DC_INTEGER, 0)
    {}

dataman::DCDecimal::DCDecimal()
    :dumisdk::DCLiteral<double>(DC_DECIMAL, 0.0f)
    {}

dataman::DCString::DCString()
    :dumisdk::DCLiteral<std::string>(DC_STRING, "")
    {}

/* DC Map */
dataman::DCMap::DCMap()
   : dumisdk::DCCollection<std::map<APPSID, dumisdk::DCMemObj*>, APPSID>(DC_MAP, {}) {}

dumisdk::DCMemObj *dataman::DCMap::operator[](APPSID id)
{
    for(auto i = __value->begin(); i != __value->end(); ++i){
        if(i->second->id == id){
            return i->second;
        }
    }

    return nullptr;
}

bool dataman::DCMap::remove(APPSID id)
{
    return __value->erase(id) > 0;
}

bool dataman::DCMap::remove(dumisdk::DCMemObj *item)
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
dataman::DCList::DCList()
    : dumisdk::DCCollection<std::vector<dumisdk::DCMemObj*>, size_t>(DC_LIST, {}) {}

dumisdk::DCMemObj *dataman::DCList::operator[](size_t index)
{
    if(index < 0 || index >= __value->size()) { return nullptr; }
    return (*__value)[index];
}

void dataman::DCList::push_back(dumisdk::DCMemObj *item)
{
    __value->push_back(item);
}

bool dataman::DCList::remove(size_t index)
{
    if(index < 0 || index >= __value->size()){ return false; }
    __value->erase(__value->begin()+index);
    return true;
}

bool dataman::DCList::remove(dumisdk::DCMemObj *item)
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
dataman::TypeTemplate::TypeTemplate(std::string name, __type_builder builder)
    :dumisdk::DCMemObj(name)
{
    this->name = name;
    this->__builder = builder;
}

dumisdk::DCMemObj *dataman::TypeTemplate::build()
{
    return __builder();
}

dataman::TypeTemplateFactory::TypeTemplateFactory(){
    
}

dataman::TypeTemplateFactory::~TypeTemplateFactory(){

    for(auto i: __templates){
        delete  i.second;
    }
}

bool dataman::TypeTemplateFactory::registerTemplate(std::string name, __type_builder builder){

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

dumisdk::DCMemObj *dataman::TypeTemplateFactory::instanceOf(std::string name)
{
    return instanceOf(FNV1A(name));
}

dumisdk::DCMemObj *dataman::TypeTemplateFactory::instanceOf(HASHID id)
{
    if(mapcontains(__templates, id)){
        auto inst = __templates[id]->build();
        return inst;
    }
    return nullptr;
}

bool dataman::TypeTemplateFactory::hasType(std::string name)
{
    return hasType(hashId(name));
}

bool dataman::TypeTemplateFactory::hasType(HASHID id)
{
    return mapcontains(__templates, id);
}

dataman::DCDataManager::DCDataManager(bool loadDefaults){
    __factory = new TypeTemplateFactory();
    if(loadDefaults){ loadDefaultTypes(); }
}

dataman::DCDataManager::~DCDataManager(){
    delete __factory;
}

APPSID dataman::DCDataManager::createVar(std::string typeName)
{
    return createVar(hashId(typeName));
}

APPSID dataman::DCDataManager::createVar(HASHID typeId)
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

dumisdk::DCMemObj *dataman::DCDataManager::requestVar(APPSID id)
{
    if(mapcontains(__dTypeStorage, id)){
        return __dTypeStorage[id];
    } else {
        return nullptr;
    }

    return __dTypeStorage.find(id) == __dTypeStorage.end() ? 
        __dTypeStorage[id] : nullptr;
}

bool dataman::DCDataManager::deleteVar(APPSID id)
{
    if(mapcontains(__dTypeStorage, id)){
        __dTypeStorage.erase(id);
        return true;
    }
    return false;
}

void dataman::DCDataManager::loadDefaultTypes(){
    auto mk_bool = [](){return (dumisdk::DCMemObj*)(new DCBoolean());};
    auto mk_integer = [](){return (dumisdk::DCMemObj*)(new DCInteger());};
    auto mk_decimal = [](){return (dumisdk::DCMemObj*)(new DCDecimal());};
    auto mk_string = [](){return (dumisdk::DCMemObj*)(new DCString());};
    auto mk_list = [](){return (dumisdk::DCMemObj*)(new DCList());};
    auto mk_map = [](){return (dumisdk::DCMemObj*)(new DCMap());};

    __factory->registerTemplate(DC_BOOL, mk_bool);
    __factory->registerTemplate(DC_INTEGER, mk_integer);
    __factory->registerTemplate(DC_DECIMAL, mk_decimal);
    __factory->registerTemplate(DC_STRING, mk_string);
    __factory->registerTemplate(DC_LIST, mk_list);
    __factory->registerTemplate(DC_MAP, mk_map);
}


