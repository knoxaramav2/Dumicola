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

    enum __serviceLifetime__{
        __DCSM_UNREGISTERED__ = 0,
        __DCSM_INSTANCE__ = 1,
        __DCSM_SINGELTON__ = 2,
        __DCSM_SCOPED__ = 4,
    };

    #define idFromTU(T, U) std::is_same<T, void>::value ? \
            std::type_index(typeid(U)) : std::type_index(typeid(U))

    struct __smTypeSlot{
        public:
        virtual ~__smTypeSlot() = default;
        virtual std::unique_ptr<__smTypeSlot> clone() const = 0;
    };

    template<typename T>
    struct __smTypeContainer: __smTypeSlot{
        __smTypeContainer() = default;
        std::unique_ptr<__smTypeSlot> clone() const override{
            return std::make_unique<__smTypeContainer<T>>();
        }
        __serviceLifetime__ getLifetime(){return __lifetime;}
        protected:
        __serviceLifetime__ __lifetime;
        __smTypeContainer(__serviceLifetime__ __lifetime) : __smTypeSlot(), __lifetime(__lifetime){}
    };

    template<typename T>
    struct __smSingeltonContainer: public __smTypeContainer<T>{
        __smSingeltonContainer():__smTypeContainer<T>(__serviceLifetime__::__DCSM_SINGELTON__){}
        std::unique_ptr<T> getInstance(){
            std::unique_ptr<T> ret;
            if(__inst == nullptr){
                ret = std::make_unique<T>();
                this->__inst = ret.get();
                return ret;
            } else {
                ret = std::unique_ptr<T>(__inst);
            }
            return ret;
        }
        private:
        T* __inst;
    };

    template<typename T>
    struct __smInstanceContainer: public __smTypeContainer<T>{
        __smInstanceContainer():__smTypeContainer<T>(__serviceLifetime__::__DCSM_INSTANCE__){}
        std::unique_ptr<T> getInstance(){ return std::make_unique<T>();}
    };

    class ServiceScope{
        std::map<std::type_index, std::unique_ptr<__smTypeSlot>> __services;
        public:
        template<typename T, typename U>
        bool registerService(){
            std::type_index sid = idFromTU(T,U);
            if(mapcontains(__services, sid)){return false;}
            __services[sid] = std::make_unique<__smInstanceContainer<U>>();
            return true;
        }

        template<typename T>
        std::unique_ptr<T> resolveType(){
            std::type_index sid = std::type_index(typeid(T));
            if(mapcontains(__services, sid)){ throw dumiexception("Unregistered scoped service"); }
            __smInstanceContainer<T> * inst = static_cast<__smInstanceContainer<T> *>(__services[sid].get());
            return inst->getInstance();
        };
    };

    class ServiceManager{

        //scopes instances
        //std::map<APPSID, ServiceScope> __scopedServices;
        //singeltons
        std::map<std::type_index, std::unique_ptr<__smTypeSlot>> __singeltonServices;
        //instances
        std::map<std::type_index, std::unique_ptr<__smTypeSlot>> __instanceServices;

        //T: Interface U: Implementation
        template<typename T, typename U>
        //bool __registerType(ServiceScope* _scope, __serviceLifetime__ lifetime){
        bool __registerType(__serviceLifetime__ lifetime){
            static_assert(!std::is_same<U, void>(), "Service implementation required");

            if(lifetime == __serviceLifetime__::__DCSM_SCOPED__){
                throw dumiexception("Scoped registration not implemented");
                //TODO
                // APPSID sid = appId(_scope);
                // if(mapcontains(__scopedServices, sid)){return false;}
                // __scopedServices[sid].registerService<T,U>();
            } else{
                std::type_index sid = idFromTU(T, U);
                if(lifetime == __serviceLifetime__::__DCSM_INSTANCE__){
                    if(mapcontains(__instanceServices, sid)){return false;}
                    __instanceServices[sid] = std::make_unique<__smInstanceContainer<U>>();
                } else {
                    if(mapcontains(__singeltonServices, sid)){return false;}
                    __singeltonServices[sid] = std::make_unique<__smSingeltonContainer<U>>();
                }
            }

            return true;
        }

        //T: Interface
        template<typename T>
        //std::unique_ptr<T> __resolveType(ServiceScope* _scope, __serviceLifetime__ lifetime)
        std::unique_ptr<T> __resolveType(__serviceLifetime__ lifetime)
        {

            if(lifetime == __serviceLifetime__::__DCSM_SCOPED__){
                throw dumiexception("Scoped resolution not implemented");
                //TODO
                //APPSID sid = appId(_scope);
                //if(!mapcontains(__scopedServices, sid)) { throw dumiexception("Unregistered service scope"); }
            } else {
                std::type_index sid(typeid(T));
                if(lifetime == __serviceLifetime__::__DCSM_INSTANCE__){
                    if(!mapcontains(__instanceServices, sid)) { throw dumiexception("Unregistered instance service"); }
                    __smInstanceContainer<T> * inst = static_cast<__smInstanceContainer<T> *>(__instanceServices[sid].get());
                    return inst->getInstance();
                } else {
                    if(!mapcontains(__singeltonServices, sid)) { throw dumiexception("Unregistered singelton service"); }
                    __smSingeltonContainer<T> * inst = static_cast<__smSingeltonContainer<T> *>(__singeltonServices[sid].get());
                    return inst->getInstance();
                }
            }

            throw dumiexception("Failed to resolve managed service");
        }

        public:

        //Registration
        template<typename T, typename U>
        bool registerSingelton(){
            return __registerType<T,U>(__serviceLifetime__::__DCSM_SINGELTON__);
        }
        template<typename U>
        bool registerSingelton(){
            return __registerType<void, U>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        template<typename T, typename U>
        bool registerInstance(){
            return __registerType<T, U>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        template<typename U>
        bool registerInstance(){
            return __registerType<void, U>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        // template<typename T, typename U>
        // bool registerScoped(ServiceScope* scope){
        //     return __registerType<T, U>(scope, __serviceLifetime__::__DCSM_SCOPED__);
        // }

        // template<typename U>
        // bool registerScoped(ServiceScope* scope){
        //     return __registerType<void, U>(scope, __serviceLifetime__::__DCSM_SCOPED__);
        // }

        //Resolution
        template<typename T>
        std::unique_ptr<T> resolveServiceInstance(){
            return __resolveType<T>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        template<typename T>
        std::unique_ptr<T> resolveServiceSingelton(){
            return __resolveType<T>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        // template<typename T>
        // std::unique_ptr<T> resolveServiceScoped(ServiceScope* scope){
        //     return __resolveType<T>(scope, __serviceLifetime__::__DCSM_SCOPED__);
        // }
    };

}

