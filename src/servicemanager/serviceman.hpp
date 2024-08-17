#pragma once

#include "dcProvider.hpp"
#include "dtypes.hpp"

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
        void addTransient(std::function<U*(Args...)> fnc) {
            registerFactory<T, U, Args...>(__DCSM_INSTANCE__, fnc);
        }

        template<typename U, typename... Args>
        void addTransient(std::function<U*(Args...)> fnc) {
            addTransient<void, U>(fnc);
        }
    };
}
