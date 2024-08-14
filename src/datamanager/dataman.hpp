#pragma once

#include <type_traits>
#include <map>
#include <typeindex>
#include <functional>

#include "dtypes.hpp"
#include "utils.hpp"

namespace dataman{

    class __TypeManager{

    };


    class TypeConverter{

        //std::map<std::pair<std::type_index, std::type_index>, std::function<void*(void*)>> _converters;
        std::map<std::pair<std::type_index, std::type_index>, std::function<void*(void*)>> _converters;
        public:

        template<typename RType, typename VType>
        bool addConverter(std::function<RType(VType)> converter){
            auto key = idPairTU(RType, VType);
            if(mapcontains(_converters, key)){ return false; }
            _converters[key] = [converter](void* value) -> void*{
                VType* tValue = static_cast<VType*>(value);
                RType res = converter(*tValue);
                return new RType(res);
            };
            return true;
        };

        template<typename RType, typename VType>
        RType convertAs(VType value){
            auto key = idPairTU(RType, VType);
            if(!mapcontains(_converters, key)){
                throw dumiexception(frmstr("Use of unregistered converter (%s -> %s)", 
                    typeid(VType).name(), typeid(RType).name()).c_str());
            }
            void* vRes = _converters[key](static_cast<void*>(&value));
            RType* tRes = static_cast<RType*>(vRes);
            RType res = *tRes;
            delete tRes;
            return res;
        }
    };

    template<typename T>
    class __MemScope{
        static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value);
        
    };

    class DataManager{

        __TypeManager _typeManager;
        TypeConverter _converters;

    public:

        TypeConverter& getConverter();

    };
};



