#pragma once

#include "dcProvider.h"
#include "dtypes.h"

namespace serviceman{

    enum __serviceLifetime__{
        __DCSM_UNREGISTERED__ = 0,
        __DCSM_INSTANCE__ = 1,
        __DCSM_SINGLETON__ = 2,
        __DCSM_SCOPED__ = 4,
    };
    
    class ServiceManager : public dumisdk::IDCFactoryStore {
    public:
        enum __serviceLifetime__ {
            __DCSM_UNREGISTERED__ = 0,
            __DCSM_INSTANCE__ = 1,
            __DCSM_SINGLETON__ = 2,
            __DCSM_SCOPED__ = 4,
        };

        template<typename T, typename... Args>
        T* resolveTransientAs(Args... args) {
            auto pArgs = std::make_tuple(args...);
            return createNew<T>(__DCSM_INSTANCE__, false, &pArgs);
        }

        template<typename T, typename U, typename... Args>
        void registerTransient(std::function<U*(Args...)> fnc) {
            registerFactory<T, U, Args...>(__DCSM_INSTANCE__, fnc);
        }

        template<typename U, typename... Args>
        void registerTransient(std::function<U*(Args...)> fnc) {
            registerTransient<void, U>(fnc);
        }
        
        template<typename T, typename... Args>
        APPSID createSingletonAs(Args... args) {
            auto pArgs = std::make_tuple(args...);
            auto pt = createNew<T>(__DCSM_SINGLETON__, true, &pArgs);
            return appId(pt);
        }

        template<typename T>
        T* resolveSingletonAs(APPSID id) {
            return resolveAs<T>(__DCSM_SINGLETON__, id);
        }

        template<typename T, typename U, typename... Args>
        void registerSingleton(std::function<U*(Args...)> fnc) {
            registerFactory<T, U, Args...>(__DCSM_SINGLETON__, fnc);
        }

        template<typename U, typename... Args>
        void registerSingleton(std::function<U*(Args...)> fnc) {
            registerSingleton<void, U>(fnc);
        }
    
    
    
    };
}
