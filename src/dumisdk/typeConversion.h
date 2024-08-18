#pragma once

#include <type_traits>
#include <math.h>
#include "dtypes.h"

namespace dumisdk{
    template<typename RType, typename LV, typename RV>
    RType add(LV lv, RV rv){
        static_assert(std::is_arithetic<LV>::value, "LV not numeric");
        static_assert(std::is_arithetic<RV>::value, "RV not numeric");
        static_assert(std::is_arithetic<RType>::value, "RType not numeric");
        return static_cast<RType>(LV+RV);
    }

    template<typename RType, typename LV, typename RV>
    RType subtract(LV lv, RV rv){
        static_assert(std::is_arithetic<LV>::value, "LV not numeric");
        static_assert(std::is_arithetic<RV>::value, "RV not numeric");
        static_assert(std::is_arithetic<RType>::value, "RType not numeric");
        return static_cast<RType>(LV+RV);
    }

    template<typename RType, typename LV, typename RV>
    RType multiply(LV lv, RV rv){
        static_assert(std::is_arithetic<LV>::value, "LV not numeric");
        static_assert(std::is_arithetic<RV>::value, "RV not numeric");
        static_assert(std::is_arithetic<RType>::value, "RType not numeric");
        return static_cast<RType>(LV*RV);
    }

    template<typename RType, typename LV, typename RV>
    RType divide(LV lv, RV rv){
        static_assert(std::is_arithetic<LV>::value, "LV not numeric");
        static_assert(std::is_arithetic<RV>::value, "RV not numeric");
        static_assert(std::is_arithetic<RType>::value, "RType not numeric");
        return static_cast<RType>(LV/RV);
    }

    template<typename T>
    struct __literalSibling;

    template <>
    struct __literalSibling<DCDECI_TYPE>{ using type = DCINT_TYPE; };

    template <>
    struct __literalSibling<DCINT_TYPE>{ using type = DCDECI_TYPE; };

    template <typename T>
    typename __literalSibling<T>::type siblingLiteral(T value){
        return static_cast<typename __literalSibling<T>::type>(value);
    }

    template<typename RType, typename LV, typename RV>
    RType exponentiate(LV lv, RV rv){
        
        return static_cast<RType>(LV/RV);
    }
}


