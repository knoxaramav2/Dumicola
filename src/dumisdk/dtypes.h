#pragma once

#include "defs.h"
#include "dumiexcept.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace dumisdk
{
    enum DCTypes{
        DCBOOL, DCINT, DCDECI,
        DCSTR, DCMAP, DCLIST
    };

    struct DCMemObj;

    typedef bool DCBOOL_TYPE;
    typedef long DCINT_TYPE;
    typedef double DCDECI_TYPE;
    typedef std::string DCSTRING_TYPE;
    typedef std::vector<DCMemObj*> DCLIST_TYPE;
    typedef std::map<APPSID, DCMemObj*> DCMAP_TYPE;

    class DCOps;
    struct DCMemObj{
        const APPSID id;
        const TypeId type;
        
        DCMemObj(TypeId id);
        virtual ~DCMemObj() = default;

        protected:
        DCMemObj();

        friend DCOps;
    };

    template<typename T>
    struct DCType: extend DCMemObj{
        ~DCType(){
            delete _value;
        }
        T& get(){ 
            return *_value;
        }
        void set(T value){ 
            *_value = value;
        }
        protected:
        DCType(T* value):DCMemObj(typeId(T)),_value(value){}
        DCType(){}
        T* _value;
    };

    template<typename T>
    struct DCLiteral: extend DCType<T>{
        protected:
        DCLiteral(){}
    };

    template<typename T>
    struct DCCollection: extend DCType<T>{
        protected:
        DCCollection(T* value):DCType<T>(value){}
        DCCollection(){}
    };

    template<typename T>
    struct DCClass: extend DCType<T>{
        protected:
        DCClass(T* value):DCType<T>(value){}
        DCClass(){}
    };

    struct DCBoolean: extend DCLiteral<DCBOOL_TYPE>{
        DCBoolean();
    };

    struct DCInteger: extend DCLiteral<DCINT_TYPE>{
        DCInteger();
    };

    struct DCDecimal: extend DCLiteral<DCDECI_TYPE>{
        DCDecimal();
    };

    struct DCString: extend DCLiteral<DCSTRING_TYPE>{
        DCString();
    };

    struct DCMap: extend DCCollection<DCMAP_TYPE>{
        DCMap();
    };

    struct DCList: extend DCCollection<DCLIST_TYPE>{
        DCList();
    };

    #define assertStdDCType(T)\
        static_assert(\
            std::is_same<T, DCBOOL_TYPE>::value ||\
            std::is_same<T, DCINT_TYPE>::value ||\
            std::is_same<T, DCDECI_TYPE>::value ||\
            std::is_same<T, DCSTRING_TYPE>::value ||\
            std::is_same<T, DCMAP_TYPE>::value || \
            std::is_same<T, DCLIST_TYPE>::value \
            ,"Non DCType default requested")

    template<typename T>
    T getTypeDefault(){
        assertStdDCType(T);
        return T();
    };

    void* initTypeDefault(DCTypes type);
    
    class DCOps{
    public:
        template<typename T>


        static void add(DCMemObj*lp, DCMemObj* rp);
        static void subtract(DCMemObj*lp, DCMemObj* rp);
    };

};
