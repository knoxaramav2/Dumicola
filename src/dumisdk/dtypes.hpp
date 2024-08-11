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
    struct DynaType{
        
    };

    class IDataManager{
        public:
        virtual APPSID createVar(std::string typeName)=0;
        virtual APPSID createVar(HASHID typeId) = 0;
        virtual DCMemObj* requestVar(APPSID id) = 0;
        virtual bool deleteVar(APPSID id) = 0;
    };
};

