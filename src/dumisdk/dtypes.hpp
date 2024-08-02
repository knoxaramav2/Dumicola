#pragma once

#include "defs.hpp"

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace dumisdk
{
    #define BYTE2 0x0000FFFF
    #define BYTE4 0xFFFF0000

    enum DumiBaseType: uint16_t{
        //Basic types
        NONE = 0,
        BOOL,
        INTEGER, DECIMAL,
        STRING,
        MAP, LIST,
        MMDT,
    };

    enum DumiExtType: uint16_t{
        BASIC_DTYPE=0,
    };

    #define DumiType uint32_t

    #define SET_DTYPE_EXT(base, ext) (DumiType)(base | (ext<<16))
    #define DTYPE_BASE(e_val) (DumiBaseType)(e_val&BYTE2)
    #define DTYPE_EXT(e_val) (DumiExtType)(e_val>>16)

    struct DCMemObj{
        APPSID id;
        DumiType type;
        DCMemObj(DumiBaseType t_base, DumiExtType t_ext);
    };

    template<typename T>
    struct DCType : DCMemObj{
        protected:
        DCType(DumiBaseType t_base, DumiExtType t_ext, T initialValue);
        ~DCType();
        T* __value;
    };

    template<typename T>
    struct DCLiteral: DCType<T>{
        DCLiteral(DumiBaseType t_base, DumiExtType t_ext, T initialValue);
        virtual T get();
        virtual void set(T value);
    };

    template<typename T, typename I>
    struct DCCollection: DCType<T>{
        DCCollection(DumiBaseType t_base, DumiExtType t_ext, T initialValue);
        virtual DCMemObj* operator[](I id);
        virtual bool remove(I id);
        virtual bool remove(DCMemObj* item);
    };

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

    typedef DCMemObj* (__type_builder)(
        DumiBaseType base,
        DumiExtType ext
    );

    struct TypeTemplate:DCMemObj{
        TypeTemplate(std::string name, __type_builder builder,
        DumiBaseType base, DumiExtType ext);
        std::string name;
        DCMemObj* build();
        private:
        __type_builder* __builder;
    };

    class TypeTemplateFactory{
        static std::vector<TypeTemplate> __templates;
        TypeTemplateFactory();
        ~TypeTemplateFactory();

        public:

        TypeTemplateFactory* getInstance();

        bool registerTemplate();
        DCMemObj* createFrom();
    };

    class DCDataManager{
        std::map<APPSID, DCMemObj*> __dTypeStorage;
    public:
        DCDataManager();
        ~DCDataManager();

        DCMemObj* createVar(DumiBaseType type, DumiExtType ext);
        DCMemObj* requestVar(APPSID id);
        bool deleteVar(APPSID id);
    };
}
