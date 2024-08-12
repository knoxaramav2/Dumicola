#pragma once

#include "dtypes.hpp"

namespace dataman
{
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
        TypeTemplateFactory __typeFactory;
        std::map<APPSID, dumisdk::DCMemObj*> __varStorage;
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

