#pragma once

#include <map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <functional>
#include <any>
#include <iostream>
#include "dumiexcept.hpp"
#include "service_interfaces.hpp"

namespace serviceman{    

    enum _serviceLifetime_{
        DCSM_UNREGISTERED_ = 0,
        DCSM_INSTANCE_ = 1,
        DCSM_SINGELTON_ = 2,
        DCSM_SCOPED_ = 4,
    };

    #define idFromTU(T, U) std::is_void<T>::value ? \
            std::type_index(typeid(U)) : std::type_index(typeid(T))
    #define idFromT(T) std::type_index(typeid(T))
    #define TFactory(T) []() -> std::unique_ptr<void>{ return std::make_unique<U>(); }

    typedef void* (*ITypeBuilder)();

    struct _smTypeSlot{
        public:
        [[nodiscard]] virtual std::unique_ptr<_smTypeSlot> clone() const = 0;
    };

    template<typename T>
    struct _smTypeContainer: _smTypeSlot{
        _smTypeContainer() = default;
        [[nodiscard]] std::unique_ptr<_smTypeSlot> clone() const override{
            return std::make_unique<_smTypeContainer<T>>();
        }
        _serviceLifetime_ getLifetime(){return _lifetime;}
        protected:
        _serviceLifetime_ _lifetime;
        explicit _smTypeContainer(_serviceLifetime_ _lifetime) : _smTypeSlot(), _lifetime(_lifetime){}
        virtual std::shared_ptr<T> getInstance(){throw dumiexception("Invalid type container");};
    };

    template<typename T>
    struct _smSingeltonContainer: public _smTypeContainer<T>{

        ITypeBuilder _builder;
        const char* _cType;

        _smSingeltonContainer():_smTypeContainer<T>(_serviceLifetime_::DCSM_SINGELTON_){
            _builder = []() -> void* {return new T();};
            _cType = typeid(T).name();
        }
        std::shared_ptr<T> getInstance() override{
            if(_inst == nullptr){
                _inst = (T*)_builder();
                _mn_ref = std::make_shared<T>(*_inst);
            }
            return _mn_ref;
        }
        private:
        T* _inst;
        std::shared_ptr<T> _mn_ref;
    };

    class ServiceManager{

        std::map<std::type_index, std::unique_ptr<_smTypeSlot>> _singeltons;
        std::map<std::type_index, ITypeBuilder> _typeFactories;

        template<typename T, typename U>
        void _registerTypeWithLifetime(_serviceLifetime_ lifetime){
            static_assert(!std::is_void<U>::value, "Factory type cannot be null");
            auto sid = idFromTU(T,U);
            if(lifetime == _serviceLifetime_::DCSM_SINGELTON_){
                _singeltons[sid] = std::make_unique<_smSingeltonContainer<U>>();
                if(std::is_base_of<dumisdk::ILogger, U>::value){
                    auto* inst = static_cast<_smSingeltonContainer<T>*>(_singeltons[sid].get());
                }
            } else if (lifetime == _serviceLifetime_::DCSM_INSTANCE_){
                _typeFactories[sid] = []() -> void* {
                    return new U();
                };
            } else{
                throw dumiexception("Illegal type lifetime registration");
            }
        }

        template<typename T>
        std::shared_ptr<T> _resolveLifetime(_serviceLifetime_ lifetime){
            auto sid = idFromT(T);

            if(lifetime == _serviceLifetime_::DCSM_INSTANCE_){
                auto it = _typeFactories.find(sid);
                if(it == _typeFactories.end()) { return nullptr; }
                auto inst = (T*) it->second();
                return std::shared_ptr<T>(inst);
            } else if (lifetime == _serviceLifetime_::DCSM_SINGELTON_){
                auto it = _singeltons.find(sid);
                if(it == _singeltons.end()) { return nullptr; }
                auto* inst = static_cast<_smSingeltonContainer<T>*>(_singeltons[sid].get());
                return inst->getInstance();
            }

            throw dumiexception("Resolve scope not implemented");
        }

        public:

        /**
         * General Registration / Resolution
         */

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerTransient(){
            _registerTypeWithLifetime<T, U>(_serviceLifetime_::DCSM_INSTANCE_);
        }

        /// @brief Register object with transient lifetime
        /// @tparam U Concrete
        template<typename U>
        void registerTransient(){
            _registerTypeWithLifetime<void, U>(_serviceLifetime_::DCSM_INSTANCE_);
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::shared_ptr<T> resolveTransient(){
            return _resolveLifetime<T>(_serviceLifetime_::DCSM_INSTANCE_);
        }

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename T, typename U>
        void registerSingelton(){
            _registerTypeWithLifetime<T,U>(_serviceLifetime_::DCSM_SINGELTON_);
        }

        /// @brief Register object with transient lifetime
        /// @tparam T Interface / Concrete
        /// @tparam U Concrete  / Void
        template<typename U>
        void registerSingelton(){
            _registerTypeWithLifetime<void,U>(_serviceLifetime_::DCSM_SINGELTON_);
        }

        /// @brief Resolve type with transient lifetime
        /// @tparam T Interface/type to resolve
        /// @return Instance of resolved type
        template<typename T>
        std::shared_ptr<T> resolveSingelton(){
            return _resolveLifetime<T>(_serviceLifetime_::DCSM_SINGELTON_);
        }

        /**
         * Special Registration / Resolution
         */
        template<typename T>
        void registerLogger(){
            static_assert(std::is_base_of<dumisdk::ILogger, T>::value, "Logger must extend ILogger");
            _registerTypeWithLifetime<dumisdk::ILogger, T>(_serviceLifetime_::DCSM_SINGELTON_);
        }

        std::shared_ptr<dumisdk::ILogger> getLogger(){
            return _resolveLifetime<dumisdk::ILogger>(_serviceLifetime_::DCSM_SINGELTON_);
        }
    };
}