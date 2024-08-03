#pragma once

#include "defs.hpp"

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace dumisdk
{
    struct DCMemObj{
        APPSID id;
        HASHID hashId;
        DCMemObj(std::string name);
    };

    template<typename T>
    struct DCType : DCMemObj{
        protected:
        DCType(std::string name, T initialValue);
        ~DCType();
        T* __value;
    };

    template<typename T>
    struct DCLiteral: DCType<T>{
        DCLiteral(std::string name, T initialValue);
        virtual T get();
        virtual void set(T value);
    };

    template<typename T, class I>
    struct DCCollection: DCType<T>{
        DCCollection(std::string name, T initialValue);
        virtual DCMemObj* operator[](I id) = 0;
        virtual bool remove(I id) = 0;
        virtual bool remove(DCMemObj* item) = 0;
    };

    // using DCBoolean = DCLiteral<bool>;
    // using DCInteger = DCLiteral<int32_t>;
    // using DCDecimal = DCLiteral<double>;
    // using DCString = DCLiteral<std::string>;

    // using DCMap = DCCollection<std::map<APPSID, DCMemObj*>, APPSID>;
    // using DCList = DCCollection<std::vector<DCMemObj*>, size_t>;
    
    struct DCBoolean: DCLiteral<bool>{ DCBoolean(); };
    struct DCInteger: DCLiteral<int32_t>{ DCInteger(); };
    struct DCDecimal: DCLiteral<double>{ DCDecimal(); };
    struct DCString: DCLiteral<std::string>{ DCString(); };

    struct DCMap: DCCollection<std::map<APPSID, DCMemObj*>, APPSID>{ 
        DCMap();
        DCMemObj* operator[](APPSID id);
        bool remove(APPSID id);
        bool remove(DCMemObj* item);
    };

    struct DCList: DCCollection<std::vector<DCMemObj*>, size_t>{ 
        DCList(); 
        DCMemObj* operator[](size_t index);
        void push_back(DCMemObj* item);
        bool remove(size_t index);
        bool remove(DCMemObj* item);
    };

    typedef DCMemObj* (__type_builder)();

    namespace __internal
    {
        struct TypeTemplate:DCMemObj{
            TypeTemplate(std::string name, __type_builder builder);
            std::string name;
            DCMemObj* build();
            private:
            __type_builder* __builder;
        };

        class TypeTemplateFactory{
            std::map<HASHID, TypeTemplate*> __templates;
            TypeTemplateFactory();
            ~TypeTemplateFactory();

            public:

            static TypeTemplateFactory* getInstance();

            bool registerTemplate(std::string name, __type_builder builder);
            DCMemObj* instanceOf(std::string name);
            DCMemObj* instanceOf(HASHID id);
            bool hasType(std::string name);
            bool hasType(HASHID id);
        };

        class DCDataManager{
            TypeTemplateFactory* __factory;
            std::map<APPSID, DCMemObj*> __dTypeStorage;
            void loadDefaultTypes();
        public:
            DCDataManager(bool loadDefaults=true);
            ~DCDataManager();

            APPSID createVar(std::string typeName);
            APPSID createVar(HASHID typeId);
            DCMemObj* requestVar(APPSID id);
            bool deleteVar(APPSID id);
        };
    }
};
