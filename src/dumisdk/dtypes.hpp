#pragma once

#include "defs.hpp"
#include "dumiexcept.hpp"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace dumisdk
{
    enum DCTypes{
        DCBOOL, DCINT, DCDECI,
        DCSTR, DCMAP, DCLIST
    };

    template<typename T>
    T defaultTypeValue();

    class DCOps;
    struct DCMemObj{
        const APPSID id;
         const TypeId type;
        //const DCTypes type;
        
        DCMemObj(TypeId id, void* value);
        virtual ~DCMemObj() = default;

        protected:
        std::shared_ptr<void*> _value;

        friend DCOps;
    };

    template<typename T>
    class DCLiteral: public DCMemObj{
        protected:
        DCLiteral(TypeId id, T* value);
    };

    template<typename T>
    class DCCollection: public DCMemObj{
        protected:
        DCCollection(TypeId id, void* value);
    };

    template<typename T>
    class DCClass: public DCMemObj{
        protected:
        DCClass(TypeId id, void* value);
    };

    typedef bool DCBOOL_TYPE;
    typedef long DCINT_TYPE;
    typedef double DCDECI_TYPE;
    typedef std::string DCSTRING_TYPE;
    typedef std::vector<DCMemObj*> DCLIST_TYPE;
    typedef std::map<APPSID, DCMemObj*> DCMAP_TYPE;

    #define assertStdDCType(T)\
        static_assert(\
            std::is_same<T, DCBOOL_TYPE>::value ||\
            std::is_same<T, DCINT_TYPE>::value ||\
            std::is_same<T, DCDECI_TYPE>::value ||\
            std::is_same<T, DCSTRING_TYPE>::value ||\
            std::is_same<T, DCMAP_TYPE>::value || \
            std::is_same<T, DCLIST_TYPE>::value \
            ,"Non DCType default requested")

    template<typename T>
    T getTypeDefault(){
        assertStdDCType(T);
        return T();
    };

    void* initTypeDefault(DCTypes type);
    
    class DCOps{
    public:
        template<typename T>


        static void add(DCMemObj*lp, DCMemObj* rp);
        static void subtract(DCMemObj*lp, DCMemObj* rp);
    };

};
