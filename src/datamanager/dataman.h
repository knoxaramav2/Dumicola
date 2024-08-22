#pragma once

#include "dcProvider.h"
#include "dtypes.h"

namespace dataman{

    class DataManager;

    class AppMemHandle{
        DataManager* _dm;
        public:
        AppMemHandle(int appId, DataManager& dataManager);
        ~AppMemHandle();
        const int dcAppId;
    };

    class DataManager: public dumisdk::IDCFactoryStore{
        public:

        template<typename T>
        void registerType(int libraryId){
            static_assert(std::is_base_of<dumisdk::DCMemObj, T>::value, 
                "Registered type must derive from DCMemObj");
            std::function<T*()> fnc = []()->T*{
                return new T();
            };
            registerFactory<void, T>(libraryId, fnc);
        }

        template<typename T> 
        APPSID newVar(AppMemHandle& app, int libId = 0){
            auto res = createNew<T>(libId, true, {}, app.dcAppId);
            return appId(res);
        }

        template<typename T>
        T* getVar(AppMemHandle& app, APPSID varId){
            return resolveAs<T>(app.dcAppId, varId);
        }

        protected:
        void freeAppMemory(AppMemHandle* app){
            clearStoredByTag(app->dcAppId);
        }

        friend AppMemHandle;
    };


}
