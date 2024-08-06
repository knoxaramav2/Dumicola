#pragma once

#include <type_traits>
#include "defs.hpp"

namespace dumisdk{

    enum ServiceLifespan{
        Singleton,
        Scoped,
    };

    class IService;
    class IServiceScope{
        APPSID __scopeId;

        virtual void onServiceExit(IService& __service) = 0;

        public:

        friend IService;
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
}



