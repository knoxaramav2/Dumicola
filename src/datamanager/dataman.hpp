#pragma once

#include "dtypes.hpp"

namespace dataman
{
    struct DCBoolean: dumisdk::DCLiteral<bool>{ DCBoolean(); };
    struct DCInteger: dumisdk::DCLiteral<int32_t>{ DCInteger(); };
    struct DCDecimal: dumisdk::DCLiteral<double>{ DCDecimal(); };
    struct DCString: dumisdk::DCLiteral<std::string>{ DCString(); };

    struct DCMap: dumisdk::DCCollection<std::map<APPSID, dumisdk::DCMemObj*>, APPSID>{ 
        DCMap();
        DCMemObj* operator[](APPSID id);
        bool remove(APPSID id);
        bool remove(DCMemObj* item);
    };

    struct DCList: dumisdk::DCCollection<std::vector<dumisdk::DCMemObj*>, size_t>{ 
        DCList(); 
        DCMemObj* operator[](size_t index);
        void push_back(DCMemObj* item);
        bool remove(size_t index);
        bool remove(dumisdk::DCMemObj* item);
    };

    typedef dumisdk::DCMemObj* (__type_builder)();

    struct TypeTemplate: dumisdk::DCMemObj{
        TypeTemplate(std::string name, __type_builder builder);
        std::string name;
        DCMemObj* build();
        private:
        __type_builder* __builder;
    };

    class TypeTemplateFactory{
        std::map<HASHID, TypeTemplate*> __templates;

        public:

        TypeTemplateFactory();
        ~TypeTemplateFactory();

        bool registerTemplate(std::string name, __type_builder builder);
        dumisdk::DCMemObj* instanceOf(std::string name);
        dumisdk::DCMemObj* instanceOf(HASHID id);
        bool hasType(std::string name);
        bool hasType(HASHID id);
    };

    class DCDataManager: dumisdk::IDataManager{
        TypeTemplateFactory* __factory;
        std::map<APPSID, dumisdk::DCMemObj*> __dTypeStorage;
        void loadDefaultTypes();
    public:
        DCDataManager(bool loadDefaults=true);
        ~DCDataManager();

        APPSID createVar(std::string typeName);
        APPSID createVar(HASHID typeId);
        dumisdk::DCMemObj* requestVar(APPSID id);
        bool deleteVar(APPSID id);
    };
}

#define __InitDumiData__ auto DataManager = new dumisdk::DCDataManager(true);
