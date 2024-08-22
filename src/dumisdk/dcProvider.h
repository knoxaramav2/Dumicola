#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <stdexcept>
#include <mutex>

#include "defs.h"
#include "dtypes.h"
#include "utils.h"

/**
 * Provides generic implementation for factories and providers
 */

namespace dumisdk
{
    template<typename U, typename... Args>
    using _factoryBuilder = std::function<U*(Args...)>;

    class BaseTypeErased{
        public:
        virtual ~BaseTypeErased() = default;
    };

    template<typename T>
    class TypeErased: public BaseTypeErased{
        public:
        TypeErased(T* inst):_inst(inst){}
        ~TypeErased(){delete _inst;}
        T* get(){return _inst;}

        private:
        T* _inst;
    };

    class IDCFactoryStore{
        public:
        virtual ~IDCFactoryStore() = default;

        protected:

        template<typename T, typename U, typename... Args>
        void registerFactory(int tag, std::function<U*(Args...)> builder){
            std::lock_guard<std::mutex> guard(_mx_factory);

            static_assert(std::is_same<void, T>::value || std::is_base_of<T, U>::value, 
                "Parameter U must derive from T");
            static_assert(!std::is_same<void, U>::value, "Parameter U must not be void");
            auto sid = idFromTU(T, U);

            std::function<std::unique_ptr<BaseTypeErased>(void*)> factory = 
                [builder](void* args) -> std::unique_ptr<BaseTypeErased>{
                    auto typedArgs = static_cast<std::tuple<Args...>*>(args);
                    return std::make_unique<TypeErased<U>>(std::apply(builder, *typedArgs));
            };

            _factories[tag][sid] = factory;
        }

        template<typename T, typename... Args>
        T* createNew(int tag, bool save, void* args, int saveAsTag=-1){
            std::lock_guard<std::mutex> guard_factory(_mx_factory);
            std::lock_guard<std::mutex> guard_store(_mx_store);

            auto factIt = _factories.find(tag);
            if(factIt == _factories.end()){
                throw dumisdk::dumiexception(dcutil::frmstr("Unable to instantiate factory: %d", tag).c_str());
            }
            
            auto sid = typeId(T);
            auto& typeMap = factIt->second;
            auto typeIt = typeMap.find(sid);
            if(typeIt == typeMap.end()){
                throw dumisdk::dumiexception(dcutil::frmstr("Unable to instantiate type: %d::%s", tag, typeid(T).name()).c_str());
            }

            std::unique_ptr<BaseTypeErased> item = typeIt->second(args);
            T* inst = static_cast<TypeErased<T>*>(item.release())->get();
            if(!inst){
                throw dumisdk::dumiexception(dcutil::frmstr("Failed to instantiate type: %d::%s", tag, typeid(T).name()).c_str());
            }

            if(save){
                auto aid = appId(inst);
                int bucket = saveAsTag == -1 ? tag : saveAsTag;
                _storage[bucket][aid] = std::make_unique<TypeErased<T>>(inst);
            }

            return inst;
        }

        template<typename T>
        T* resolveAs(int tag, APPSID id){
            std::lock_guard<std::mutex> guard(_mx_store);

            auto storeIt = _storage.find(tag);
            if(storeIt == _storage.end()){
                throw dumisdk::dumiexception(dcutil::frmstr("Unable to resolve store tag %d", tag).c_str());
            }

            auto& idMap = storeIt->second;
            auto idIt = idMap.find(id);
            if(idIt == idMap.end()){
                throw dumisdk::dumiexception(dcutil::frmstr("Unable to resolve type: %d::%lx", tag, id).c_str());
            }

            T* inst = static_cast<TypeErased<T>*>(idIt->second.get())->get();
            if(!inst){
                throw dumisdk::dumiexception(dcutil::frmstr("Failed to resolve type: %d::%lx", tag, id).c_str());
            }

            return inst;
        }

        void clearStoredByTag(int tag){
            auto it = _storage.find(tag);
            if(it == _storage.end()){ return; }
            _storage.erase(tag);
        }

        private:
        std::map<int, std::map<TypeId, std::function<std::unique_ptr<BaseTypeErased>(void*)>>> _factories;
        std::map<int, std::map<APPSID, std::unique_ptr<BaseTypeErased>>> _storage; 
        std::mutex _mx_factory;
        std::mutex _mx_store;
    };
}