#pragma once

#include <map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <functional>
#include <any>
#include <iostream>
#include "dumiexcept.hpp"

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

    class ServiceManager{

        // std::unordered_map<std::type_index, std::function<std::any()>> 
        // // std::unordered_map<std::type_index, std::function<void*()>> 
        //     __typeFactories;

        std::map<std::type_index, __ITypeBuilder> __typeFactories;

        template<typename T, typename U>
        void __registerFactory(){
            static_assert(!std::is_void<U>::value, "Factory type cannot be null");
            std::type_index sid = idFromTU(T, U);

            __typeFactories[sid] = []() -> void* {
                return new U();
            };
        }

        template<typename T>
        std::unique_ptr<T> __resolveInstance(__serviceLifetime__ lifetime){
            std::type_index sid = idFromT(T);
            auto it = __typeFactories.find(sid);
            if(it == __typeFactories.end()) { return nullptr; }

            if(lifetime == __serviceLifetime__::__DCSM_INSTANCE__){
                auto inst = (T*) it->second();
                return std::unique_ptr<T>(inst);
            } else if (lifetime == __serviceLifetime__::__DCSM_SINGELTON__){

            }

            throw dumiexception("Resolve scope not implemented");
        }

        public:


        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerTransient(){
            __registerFactory<T,U>();
            //TODO...
        }

        /// @brief Register object with transient lifetime
        /// @tparam U Concrete
        template<typename U>
        void registerTransient(){
            __registerFactory<void,U>();
            //TODO...
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::unique_ptr<T> resolveTransient(){
            return __resolveInstance<T>(__serviceLifetime__::__DCSM_INSTANCE__);
            // return static_cast<T>(__resolveInstance<T>(__serviceLifetime__::__DCSM_INSTANCE__)
            // .release());
        }

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerSingelton(){
            __registerFactory<T,U>();
            //TODO...
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::unique_ptr<T> resolveSingelton(){

            return resolveTransient<T>();

            // return static_cast<T>(__resolveInstance<T>(__serviceLifetime__::__DCSM_SINGELTON__)
            // .release());
        }

    };
}