#pragma once

#include <type_traits>
#include <map>
#include <typeindex>
#include <functional>
#include <memory>

#include "dtypes.hpp"
#include "utils.hpp"

namespace dataman{

    class __typeFactoryBase{
        public:
        virtual ~__typeFactoryBase() = default;
        virtual void* create() const = 0;
    };

    template<typename T>
    class __typeFactory: public __typeFactoryBase{
        public:
        explicit __typeFactory(std::function<T*()> _factory): createFactory(std::move(_factory)){}
        void* create() const override{
            return createFactory();
        }
        private:
        std::function<T*()> createFactory;
    };

    class __TypeManager{
        
        std::map<std::type_index, std::unique_ptr<__typeFactoryBase>> _factories;

        void _registerType();
        
        public:

        template<typename T>
        void registerType(std::function<T*()> factory){
            auto sid = idFromT(T);
            if(mapcontains(_factories, sid))
            { 
                throw dumiexception(frmstr("Reregistration of type: %s", typeid(T).name()).c_str()); 
            }
            
            _factories[sid] = std::make_unique<__typeFactory<T>>(std::move(factory));
        }

        template<typename T>
        std::unique_ptr<T> create(){
            auto sid = idFromT(T);
            if(!mapcontains(_factories, sid)) { return nullptr; }
            return std::unique_ptr<T>(static_cast<T*>(
                _factories[sid]->create()
            ));
        }
    };

    class __TypeClassConverterBase{
        public:
        virtual ~__TypeClassConverterBase() = default;
        virtual void* create() const = 0;
    };

    template<typename T>
    class __TypeClassConverter: public __TypeClassConverterBase{
        static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value, "Registered type not derived from DCMemObj");
        public:
        explicit __typeFactory(std::function<T*()> _factory): createFactory(std::move(_factory)){}
        void* create() const override{
            return createFactory();
        }
        private:
        std::function<T*()> createFactory;
    };

    class TypeConverter{

        //std::map<std::pair<std::type_index, std::type_index>, std::function<void*(void*)>> _converters;
        std::map<std::pair<std::type_index, std::type_index>, std::unique_ptr<__TypeClassConverterBase>> _converters;
        public:

        template<typename RType, typename VType>
        bool addConverter(std::function<RType(VType)> converter){
            auto key = idPairTU(RType, VType);
            if(mapcontains(_converters, key)){ return false; }

            return true;
        };

        template<typename RType, typename VType>
        RType convertAs(VType value){
            auto key = idPairTU(RType, VType);
            if(!mapcontains(_converters, key)){
                throw dumiexception(frmstr("Use of unregistered converter (%s -> %s)", 
                    typeid(VType).name(), typeid(RType).name()).c_str());
            }
            // void* vRes = _converters[key](static_cast<void*>(&value));
            // RType* tRes = static_cast<RType*>(vRes);
            // RType res = *tRes;
            // delete tRes;
            return nullptr;
        }
    };

    template<typename T>
    class __MemScope{
        static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value);
        
    };

    class DataManager{

        __TypeManager _typeManager;
        TypeConverter _converters;

        void _loadDefaultTypes();

    public:

        TypeConverter& getConverter();


    };
};



