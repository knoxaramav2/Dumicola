// #pragma once

// #include <type_traits>
// #include <map>
// #include <typeindex>
// #include <functional>
// #include <memory>

// #include "dtypes.hpp"
// #include "utils.hpp"

// namespace dataman{

//     typedef void* (*__IVarBuilder)();

//     class __typeFactoryBase{
//         public:
//         virtual ~__typeFactoryBase() = default;
//         virtual void* create() const = 0;
//     };

//     template<typename T>
//     class __typeFactory: public __typeFactoryBase{
//         public:
//         explicit __typeFactory(std::function<T*()> _factory): createFactory(std::move(_factory)){}
//         void* create() const override{
//             return createFactory();
//         }
//         private:
//         std::function<T*()> createFactory;
//     };

//     class __TypeManager{
        
//         std::map<std::type_index, std::unique_ptr<__typeFactoryBase>> _factories;
        
//         public:

//         template<typename T>
//         void registerType(std::function<T*()> factory){
//             auto sid = typeId(T);
//             if(mapcontains(_factories, sid))
//             { 
//                 throw dumiexception(frmstr("Re-registration of type: %s", typeid(T).name()).c_str()); 
//             }
            
//             _factories[sid] = std::make_unique<__typeFactory<T>>(std::move(factory));
//         }

//         template<typename T>
//         std::unique_ptr<T> create(){
//             auto sid = typeId(T);
//             if(!mapcontains(_factories, sid)) { return nullptr; }
//             return std::unique_ptr<T>(static_cast<T*>(
//                 _factories[sid]->create()
//             ));
//         }
//     };

//     class __TypeClassConverterBase{
//         public:
//         virtual ~__TypeClassConverterBase() = default;
//         virtual void* create() const = 0;
//     };

//     template<typename T, typename U>
//     class __TypeClassConverter: public __TypeClassConverterBase{
//         static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value, "Registered type not derived from DCMemObj");
//         std::function<void(T,U)> _caster;
//         public:
//         __TypeClassConverter(std::function<void(T&,U&)> converter){
//             _caster = converter;
//         }
//         void convertAs(T from, U to){
//             _caster(from, to);
//         }

//     };

//     class TypeConverter{

//         std::map<std::pair<std::type_index, std::type_index>, std::function<void*(void*)>> _converters;
//         public:

//         template<typename RType, typename VType>
//         bool addConverter(std::function<void(RType&, VType&)> converter){
//             auto key = idPairTU(RType, VType);
//             if(mapcontains(_converters, key)){ return false; }
//             _converters[key] = __TypeClassConverter(converter);
//             return true;
//         };

//         template<typename VType, typename RType>
//         void convertAs(VType&from, RType&to){
//             static_assert(std::is_base_of<dumisdk::DCMemObj, RType>::value);
//             static_assert(std::is_base_of<dumisdk::DCMemObj, VType>::value);
//             auto key = idPairTU(RType, VType);
//             if(!mapcontains(_converters, key)){
//                 throw dumiexception(frmstr("Use of unregistered converter (%s -> %s)", 
//                     typeid(VType).name(), typeid(RType).name()).c_str());
//             }
//             _converters[key](from, to);
//         }
//     };

//     template<typename T>
//     class __MemScope{
//         static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value);
        
//     };

//     class DataManager{

//         __TypeManager _typeManager;
//         TypeConverter _converters;

//         void _loadDefaultTypes();

//     public:

//         TypeConverter& getConverter();


//     };
// };



