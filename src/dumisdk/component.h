#include "dtypes.h"
#include "defs.h"
#include "dumiexcept.h"

#include <memory>
#include <exception>

#pragma region IDC_Basic

namespace dumisdk{

    #pragma region DC_INTERFACES

    class IDCDefinition{
    public:
        IDCDefinition(HASHID id , HASHID parentId);

        const HASHID id;
        const HASHID parentId;
    };

    class IDCImplementation: extend IDCDefinition{

    public:
        IDCImplementation(HASHID id, HASHID parentId);

    protected:
        IDCImplementation();

    };
    template<typename T>
    using ComponentFactory = T* (*)();

    template<typename T>
    class IDCTemplate: extend IDCDefinition{

        ComponentFactory<T> _factory;
    public:
        IDCTemplate(HASHID id, HASHID parentId, ComponentFactory<T> factory):
            IDCDefinition(id, parentId),_factory(factory){}
        virtual T* create(){
            return (T*)_factory();
        }

    protected:
        IDCTemplate(ComponentFactory<T>factory):IDCDefinition(0,0),_factory(factory){};
    };

    #pragma endregion

    #pragma region DC_NodeIO

    class IONodeDefinition: extend IDCDefinition{

    public:
        //IONodeDefinition(HASHID id, HASHID parentId, dumisdk::DCVar value);

    protected:
        //IONodeDefinition(dumisdk::DCVar value);
        //const dumisdk::DCVar _value;
    };

    class DCInputDefinition: extend IONodeDefinition{
    public:
        DCInputDefinition(HASHID id, HASHID parentId);

    protected:
        DCInputDefinition();
    };

    class DCInput: extend DCInputDefinition{

    public:
        DCInput(HASHID id, HASHID parentId);

    protected:
        DCInput();
    };

    class DCInputTemplate: extend DCInputDefinition, extend IDCTemplate<DCInput>{
    
    public:

    protected:
    
    };

    #pragma endregion

    #pragma region DC_BASE_CLASSES


    class DCComponentDefinition: extend IDCDefinition{

    public:
        DCComponentDefinition(HASHID id, HASHID parentId);

    protected:
        DCComponentDefinition();

    };

    #pragma endregion

}


