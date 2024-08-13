#pragma once

#include "defs.hpp"
#include "dumiexcept.hpp"

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace dumisdk
{
    enum DCTypes{
        DCBOOL, DCINT, DCDECI,
        DCSTR, DCMAP, DCLIST
    };

    template<typename T>
    T defaultTypeValue();

    struct DCMemObj{
        const APPSID id;
        const DCTypes type;
        
        DCMemObj(DCTypes type);

        protected:
        void* _value;
    };

    typedef bool DCBOOL_TYPE;
    typedef long DCINT_TYPE;
    typedef double DCDECI_TYPE;
    typedef std::string DCSTRING_TYPE;
    typedef std::vector<DCMemObj*> DCLIST_TYPE;
    typedef std::map<APPSID, DCMemObj*> DCMAP_TYPE;

    template<typename T>
    T getTypeDefault(){
        static_assert(
            std::is_same<T, DCBOOL_TYPE>::value ||
            std::is_same<T, DCINT_TYPE>::value ||
            std::is_same<T, DCDECI_TYPE>::value ||
            std::is_same<T, DCSTRING_TYPE>::value ||
            std::is_same<T, DCMAP_TYPE>::value ||
            std::is_same<T, DCLIST_TYPE>::value  
            ,"Non DCType default requested"
        );
        return T();
    };

    void* initTypeDefault(DCTypes type);
    

};
