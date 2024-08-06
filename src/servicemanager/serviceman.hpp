#pragma once

#include "service_interfaces.hpp"
#include <vector>

namespace serviceman{

    #define __svm_tmpl__(base) template <typename T> typename \
        std::enable_if<std::is_base_of<base, T>::value>::type

    class ServiceManager{

        public:
        void addSingelton();
        bool addScoped();
        dumisdk::IServiceScope* createScope();
        void releaseScope();
    };
}

