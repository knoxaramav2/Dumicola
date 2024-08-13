#include "dtypes.hpp"
#include "defs.hpp"
#include "dumiexcept.hpp"

#include <memory>
#include <exception>

#pragma region IDC_Basic

namespace dumisdk{

    class IDCCompDef{
    public:
        IDCCompDef(HASHID id , HASHID parentId);

        const HASHID id;
        const HASHID parentId;
    };

    class IDCComp: public virtual IDCCompDef{

        public:
        IDCComp(HASHID id, HASHID parentId);

        protected:
        IDCComp();

    };

    //typedef IDCComp* (*__ComponentFactory)();
    template<typename T>
    using ComponentFactory = T* (*)();

    template<typename T>
    class IDCCompTemplate: public virtual IDCCompDef{

        ComponentFactory<T> _factory;
        public:
        IDCCompTemplate(HASHID id, HASHID parentId, ComponentFactory<T> factory):
            IDCCompDef(id, parentId), _factory(factory){}
        virtual T* create(){
            return (T*)_factory();
        }

    };

}


