#pragma once

#include "service_interfaces.hpp"
#include "defs.hpp"
#include <map>
#include <typeinfo>

namespace serviceman{

    #define __svm_tmpl__(base) template <typename T> typename \
        std::enable_if<std::is_base_of<base, T>::value>::type

    struct ServiceMapper{
        std::map<size_t, dumisdk::IServiceBuilder> __scopedServices;
        std::map<size_t, dumisdk::IServiceBuilder> __instanceServices;
        std::map<size_t, dumisdk::IServiceBuilder> __lifetimeServices;

        //template<typename T>
        
        template <typename T> typename \
        std::enable_if<std::is_base_of<dumisdk::IService, T>::value>::type
        addScoped(){
            auto hash = typeid(T).hash_code();
            if(__scopedServices.contains(hash)){ return false; }
            __scopedServices[hash] = 
            return true;
        }
    };

    class ServiceManager : dumisdk::IServiceManager{

        ServiceMapper __mapper;

        public:

        __svm_tmpl__(dumisdk::IServiceBuilder) addSingeltonService(){
            T();
            __scopedServices.push_back(T);
            auto x = __scopedServices[0];
            auto a = (x)();
        }

        // void addInstanceService();
        // void addSingeltonService();
        // bool addScopedService();

        // void addNetworkService();
        // void addDbService();

        // dumisdk::IServiceScope* createScope();
        // void releaseScope();
    };
}

