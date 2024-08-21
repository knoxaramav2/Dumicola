#include "dtypes.h"
#include "defs.h"
#include "dumiexcept.h"

#include <memory>
#include <exception>

#pragma region IDC_Basic

namespace dumisdk{

    class IDCLibrary;

    class DCDefinition{
        protected:
        DCDefinition(DCDefinition& definition);
        DCDefinition(HASHID id, HASHID parentId);
        DCDefinition();
        public:
        virtual ~DCDefinition() = default;
        const HASHID id;
        const HASHID parentId;
    };

    class DCImplementation: extend DCDefinition{
        protected:
        DCImplementation(HASHID id, HASHID parentId);
        DCImplementation();
        public:
        virtual ~DCImplementation() = default;
        virtual void update() = 0;
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
        const char* version;
        const char* author;
        const char* repository;
        const char* description;
        const APPSID libraryId;
        public:
        ComponentInfo(const char* name, const char* version, const char* author, 
            const char* repository, const char* description, APPSID libraryId);
    };

    class DCComponentDefinition: extend DCDefinition{
        protected:
        DCComponentDefinition(HASHID id, HASHID parentId);
        DCComponentDefinition();
        public:
        virtual ~DCComponentDefinition() = default;
    };

    template<typename T>
    class DCComponentTemplate;

    class DCComponentImplementation: extend DCImplementation, extend DCComponentDefinition{
        protected:
        using DCImplementation::DCImplementation;
        using DCComponentDefinition::DCComponentDefinition;
        DCComponentImplementation();
        public:
        DCComponentImplementation(DCComponentDefinition& definition);
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

    class IDCLibrary: public ComponentInfo{
        public:

        protected:
        IDCLibrary(const char* name, const char* version, const char* author, 
            const char* repository, const char* description);
        virtual const std::vector<ComponentInfo> manifest() = 0;
        virtual const DCComponentImplementation* create(const char* name) = 0;
        virtual const DCComponentImplementation* create(HASHID id) = 0;
        virtual bool registerTemplate(DCComponentTemplate<DCComponentImplementation>&
            componentTemplate) = 0;

        optmap<HASHID, std::shared_ptr<DCComponentTemplate<DCComponentImplementation>>> _templates;
        public:
        virtual ~IDCLibrary() = default;
    };

    #pragma endregion

}

typedef __declspec (dllexport) dumisdk::IDCLibrary* DUMIEXPORT;
typedef __declspec (dllimport) dumisdk::IDCLibrary* DUMIIMPORT;
