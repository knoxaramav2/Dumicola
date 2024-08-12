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
        DCType(std::string name, T initialValue) : DCMemObj(name){
            __value = new T(initialValue);
        }
        ~DCType(){ delete __value; }
        T* __value;
    };

    template<typename T>
    struct DCLiteral: DCType<T>{
        DCLiteral(std::string name, T initialValue): DCType<T>(name, initialValue){}
        virtual T get() { return *this->__value; }
        virtual void set(T value){
            *this->__value = value;
        }
    };

    template<typename T, class I>
    struct DCCollection: DCType<T>{
        DCCollection(std::string name, T initialValue):DCType<T>(name, initialValue){}
        virtual DCMemObj* operator[](I id) = 0;
        virtual bool remove(I id) = 0;
        virtual bool remove(DCMemObj* item) = 0;
    };

    /// @brief Dynamic type for DC programs
    struct DCVar{
        
    };

    class IDataManager{
        public:
        virtual APPSID createVar(std::string typeName)=0;
        virtual APPSID createVar(HASHID typeId) = 0;
        virtual DCMemObj* requestVar(APPSID id) = 0;
        virtual bool deleteVar(APPSID id) = 0;
    };

    #define DC_BOOL "__DC_IT_BOOL"
    #define DC_INTEGER "__DC_IT_INTEGER"
    #define DC_DECIMAL "__DC_IT_DECIMAL"
    #define DC_STRING "__DC_IT_STRING"
    #define DC_MAP "__DC_IT_MAP"
    #define DC_LIST "__DC_IT_LIST"

    enum DCTypes{
        DCBOOL, DCINT, DCDECI,
        DCSTR, DCMAP, DCLIST
    };

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
};

