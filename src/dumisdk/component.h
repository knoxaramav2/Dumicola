#include "dtypes.h"
#include "defs.h"
#include "dumiexcept.h"

#include <memory>
#include <exception>

#pragma region IDC_Basic

namespace dumisdk{

    class DCDefinition{
        protected:
        DCDefinition(HASHID id, HASHID parentId);
        public:
        virtual ~DCDefinition() = default;
        const HASHID id;
        const HASHID parentId;
    };

    class DCImplementation: extend DCDefinition{
        protected:
        DCImplementation(HASHID id, HASHID parentId);
        public:
        virtual ~DCImplementation() = default;
    };

    template<typename T>
    class DCInterface: extend DCDefinition{
        static_assert(std::is_base_of<DCImplementation, T>::value, "T must extend DCImplementation");
        protected:
        DCInterface(HASHID id, HASHID parentId): DCDefinition(id, parentId) {}
        public:
        virtual ~DCInterface() = default;
        virtual T* create() = 0;
    };

    struct ComponentInfo{
        const char* name;
        const HASHID componentId;
        const char* description;
        public:
        ComponentInfo(const char* name, const char* description);
    };

    class DCComponentDefinition: extend DCDefinition{
        protected:
        DCComponentDefinition(HASHID id, HASHID parentId);
        public:
        virtual ~DCComponentDefinition() = default;
    };

    template<typename T>
    class DCComponentTemplate;

    class DCComponentImplementation: extend DCImplementation, extend DCComponentDefinition{
        protected:
        using DCImplementation::DCImplementation;
        using DCComponentDefinition::DCComponentDefinition;
        public:
        DCComponentImplementation(DCComponentDefinition&);
        virtual ~DCComponentImplementation() = default;
    };

    template<typename T>
    class DCComponentTemplate: extend DCInterface<T>, extend DCComponentDefinition{
        static_assert(std::is_base_of<DCComponentImplementation, T>::value, "T must extend DCComponentImplementation");
        protected:
        using DCInterface<T>::DCInterface;
        using DCComponentDefinition::DCComponentDefinition;
        public:
        virtual ~DCComponentTemplate() = default;
    };

    #pragma region DC_LIBRARY

    class IDCLibrary{
        public:
        const char* name;
        const char* version;
        const char* author;
        const char* repository;
        const char* description;
        const APPSID libraryId;

        protected:
        IDCLibrary(const char* name, const char* version, const char* author, 
            const char* repository, const char* description);
        virtual const std::vector<ComponentInfo> manifest() = 0;
        virtual const DCComponentImplementation* create(const char* name) = 0;
        virtual const DCComponentImplementation* create(HASHID id) = 0;
        bool registerTemplate(DCComponentTemplate<DCComponentImplementation>
            componentTemplate);

        optmap<HASHID, std::shared_ptr<DCComponentTemplate<DCComponentImplementation>>> _templates;
        public:
        virtual ~IDCLibrary() = default;
    };

    #pragma endregion

}


