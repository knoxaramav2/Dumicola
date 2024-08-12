#include "dataman.hpp"
#include "maputil.hpp"

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

dataman::DCDataManager::DCDataManager(bool loadDefaults)
    :__typeFactory(){
    if(loadDefaults){ loadDefaultTypes(); }
}

dataman::DCDataManager::~DCDataManager(){

}

APPSID dataman::DCDataManager::createVar(std::string typeName)
{
    return createVar(hashId(typeName));
}

APPSID dataman::DCDataManager::createVar(HASHID typeId)
{
    bool hasType = __typeFactory.hasType(typeId);
    static uintptr_t utest = 0;

    if(__typeFactory.hasType(typeId)){
        auto typeInst = __typeFactory.instanceOf(typeId);
        auto instId = appId(typeInst);
        utest = instId;
        __varStorage[instId] = typeInst;
        return instId;
    }
    return 0;
}

dumisdk::DCMemObj *dataman::DCDataManager::requestVar(APPSID id)
{
    return mapcontains(__varStorage, id) ?
        __varStorage[id] : nullptr;
}

bool dataman::DCDataManager::deleteVar(APPSID id)
{
    if(mapcontains(__varStorage, id)){
        __varStorage.erase(id);
        return true;
    }
    return false;
}

void dataman::DCDataManager::loadDefaultTypes(){
    auto mk_bool = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCBoolean());};
    auto mk_integer = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCInteger());};
    auto mk_decimal = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCDecimal());};
    auto mk_string = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCString());};
    auto mk_list = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCList());};
    auto mk_map = [](){return (dumisdk::DCMemObj*)(new dumisdk::DCMap());};

    __typeFactory.registerTemplate(DC_BOOL, mk_bool);
    __typeFactory.registerTemplate(DC_INTEGER, mk_integer);
    __typeFactory.registerTemplate(DC_DECIMAL, mk_decimal);
    __typeFactory.registerTemplate(DC_STRING, mk_string);
    __typeFactory.registerTemplate(DC_LIST, mk_list);
    __typeFactory.registerTemplate(DC_MAP, mk_map);
}


