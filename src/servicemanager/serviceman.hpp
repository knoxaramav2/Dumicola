#pragma once

#include "service_interfaces.hpp"
#include "defs.hpp"
#include "maputil.hpp"
#include "dc_string.hpp"
#include "dumiexcept.hpp"
#include <map>
#include <typeindex>
#include <typeinfo>
#include <memory>

namespace serviceman{

    struct __smEntrySlot{
        public:
        virtual ~__smEntrySlot() = default;
        virtual std::unique_ptr<__smEntrySlot> clone() const = 0;
    };

    template<typename T>
    struct __smTypeContainer: __smEntrySlot{
        public:
        __smTypeContainer() = default;
        std::unique_ptr<__smEntrySlot> clone() const override{
            return std::make_unique<__smTypeContainer<T>>();
        }
    };

    class ServiceManager{

        std::map<std::type_index, std::unique_ptr<__smEntrySlot>> __serviceList;

        template<typename T>
        bool __registerType(){

            std::type_index sid(typeid(T));
            if(mapcontains(__serviceList, sid)){ return false; }

            __serviceList[sid] = std::make_unique<__smTypeContainer<T>>();

            return true;
        }

        template<typename T>
        std::unique_ptr<T> __resolveType(){

            std::type_index sid(typeid(T));
            if(!mapcontains(__serviceList, sid)){
                throw dumiexception("Failed to resolve managed service");
            }

            return std::make_unique<T>();
        }

        public:

        template<typename T>
        bool registerSingelton(){
            return __registerType<T>();
        }

        template<typename T>
        std::unique_ptr<T> resolveService(){
            return __resolveType<T>();
        }

    };

}

