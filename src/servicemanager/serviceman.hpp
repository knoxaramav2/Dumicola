#pragma once

#include <map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <functional>
#include <any>
#include <iostream>
#include "dumiexcept.hpp"
#include "service_interfaces.hpp"

namespace serviceman{    

    enum __serviceLifetime__{
        __DCSM_UNREGISTERED__ = 0,
        __DCSM_INSTANCE__ = 1,
        __DCSM_SINGELTON__ = 2,
        __DCSM_SCOPED__ = 4,
    };

    #define idFromTU(T, U) std::is_void<T>::value ? \
            std::type_index(typeid(U)) : std::type_index(typeid(T))
    #define idFromT(T) std::type_index(typeid(T))
    #define TFactory(T) []() -> std::unique_ptr<void>{ return std::make_unique<U>(); }

    typedef void* (*__ITypeBuilder)();

    struct __smTypeSlot{
        public:
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
        virtual std::shared_ptr<T> getInstance(){throw dumiexception("Invalid type container");};
    };

    template<typename T>
    struct __smSingeltonContainer: public __smTypeContainer<T>{

        __ITypeBuilder __builder;
        const char* __cType;

        __smSingeltonContainer():__smTypeContainer<T>(__serviceLifetime__::__DCSM_SINGELTON__){
            __builder = []() -> void* {return new T();};
            __cType = typeid(T).name();
        }
        std::shared_ptr<T> getInstance() override{
            if(__inst == nullptr){
                __inst = (T*)__builder();
                __mn_ref = std::make_shared<T>(*__inst);
            }
            return __mn_ref;
        }
        private:
        T* __inst;
        std::shared_ptr<T> __mn_ref;
    };

    class ServiceManager{

        friend class ServiceBuilder;

        std::map<std::type_index, std::unique_ptr<__smTypeSlot>> __singeltons;
        std::map<std::type_index, __ITypeBuilder> __typeFactories;

        template<typename T, typename U>
        void __registerTypeWithLifetime(__serviceLifetime__ lifetime){
            static_assert(!std::is_void<U>::value, "Factory type cannot be null");
            auto sid = idFromTU(T,U);
            if(lifetime == __serviceLifetime__::__DCSM_SINGELTON__){
                __singeltons[sid] = std::make_unique<__smSingeltonContainer<U>>();
                if(std::is_base_of<dumisdk::ILogger, U>::value){
                    __smSingeltonContainer<T>* inst = static_cast<__smSingeltonContainer<T>*>(__singeltons[sid].get());
                }
            } else if (lifetime == __serviceLifetime__::__DCSM_INSTANCE__){
                __typeFactories[sid] = []() -> void* {
                    return new U();
                };
            } else{
                throw dumiexception("Illegal type lifetime registration");
            }
        }

        template<typename T>
        std::shared_ptr<T> __resolveLifetime(__serviceLifetime__ lifetime){
            std::type_index sid = idFromT(T);

            if(lifetime == __serviceLifetime__::__DCSM_INSTANCE__){
                auto it = __typeFactories.find(sid);
                if(it == __typeFactories.end()) { return nullptr; }
                auto inst = (T*) it->second();
                return std::shared_ptr<T>(inst);
            } else if (lifetime == __serviceLifetime__::__DCSM_SINGELTON__){
                auto it = __singeltons.find(sid);
                if(it == __singeltons.end()) { return nullptr; }
                __smSingeltonContainer<T>* inst = static_cast<__smSingeltonContainer<T>*>(__singeltons[sid].get());
                return inst->getInstance();
            }

            throw dumiexception("Resolve scope not implemented");
        }

        public:

        /**
         * General Registration / Resolution
         */

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerTransient(){
            __registerTypeWithLifetime<T, U>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        /// @brief Register object with transient lifetime
        /// @tparam U Concrete
        template<typename U>
        void registerTransient(){
            __registerTypeWithLifetime<void, U>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::shared_ptr<T> resolveTransient(){
            return __resolveLifetime<T>(__serviceLifetime__::__DCSM_INSTANCE__);
        }

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerSingelton(){
            __registerTypeWithLifetime<T,U>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename U>
        void registerSingelton(){
            __registerTypeWithLifetime<void,U>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::shared_ptr<T> resolveSingelton(){

            return __resolveLifetime<T>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        /**
         * Special Registration / Resolution
         */
        template<typename T>
        void registerLogger(){
            static_assert(std::is_base_of<dumisdk::ILogger, T>::value, "Logger must extend ILogger");
            __registerTypeWithLifetime<dumisdk::ILogger, T>(__serviceLifetime__::__DCSM_SINGELTON__);
        }

        std::shared_ptr<dumisdk::ILogger> getLogger(){
            return resolveSingelton<dumisdk::ILogger>();
        }
    };

    class ServiceBuilder{
        
        ServiceManager* _sm;

        public:


        ServiceBuilder(ServiceManager& sm){ _sm = &sm; }

        template<typename T>
        void registerTransient(){_sm->registerTransient<T>();}
        template<typename T, typename U>
        void registerTransient(){_sm->registerTransient<T, U>();}

        template<typename T>
        void registerSingelton(){_sm->registerSingelton<T>();}
        template<typename T, typename U>
        void registerSingelton(){_sm->registerSingelton<T, U>();}

        template<typename T>
        void registerLogger(){_sm->registerLogger<T>();}

    };
}