#pragma once

#include "defs.hpp"

#include <string>
#include <vector>
#include <map>

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
        virtual T get();
        virtual int set(T);

        protected:
        DCType(DumiBaseType t_base, DumiExtType t_ext, T initialValue);
        ~DCType();
        T* __value;

    };

    struct DCBoolean: DCType<bool>{ DCBoolean(); };
    struct DCInteger: DCType<int32_t>{ DCInteger(); };
    struct DCDecimal: DCType<double>{ DCDecimal(); };
    struct DCString: DCType<std::string>{ DCString(); };
    struct DCMap: DCType<std::map<APPSID, DCMemObj*>>{ 
        DCMap();
        DCMemObj* operator[](APPSID id);
        //bool remove(APPSID id);
        //bool remove(DCMemObj* item);
    };
    struct DCList: DCType<std::vector<DCMemObj*>>{ DCList(); };

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
