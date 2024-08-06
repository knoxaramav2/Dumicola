#pragma once

#include <type_traits>
#include "defs.hpp"

namespace dumisdk{

    enum ServiceLifespan{
        SL_INSTANCE,
        SL_SINGELTON,
        SL_SCOPED,
    };

    class IService;
    class IServiceScope{
        APPSID __scopeId;

        virtual void onServiceExit(IService& __service) = 0;

        public:

        friend IService;
    };

    class IScopedProvider{
        public:
        
    };

    class IService{
        IServiceScope* __scope;
        ~IService(){ __scope->onServiceExit(*this); }
        public:
        IService(IServiceScope& scope){this->__scope = &scope;}
    };

    class IDbService: IService{
        public:
    };

    class INetworkService: IService{
        public:
    };

    class IServiceManager{
        public:
        
    };
}



