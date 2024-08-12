#include "dtypes.hpp"
#include "defs.hpp"

#pragma region IDC_Basic

/// @brief Common component/template data
struct IDCBase{
    HASHID id;
    HASHID parentId;
};

/* Forward declares */
struct IDCInputTemplate;
struct IDCOutputTemplate;
struct IDCFieldTemplate;
struct IDCViewTemplate;

struct IDCObject: public IDCBase{};

/// @brief Base template interface
/// @tparam T Type of component
template<typename T>
struct IDCTemplate: public IDCBase{
    static_assert(std::is_base_of<T, IDCObject>::value);
    T* createInstance() = 0;
};

#pragma endregion IDC_Basic

#pragma region IDC_Library

struct IDCLibrary{
    const char* name;
    const char* version;
    const char* description;
    const char* platform;
    const char* author;
    const char* repository;
    const char* description;
    
    HASHID id;
    //const std::vector<IDCComponentTemplate<IDCComponent>> getComponents();
    //IDComponent* getComponent();
};

#pragma endregion IDC_Library

#pragma region IDC_Field

struct IDCFieldDefinition: public IDCBase{
    bool visible;
};

struct IDCFieldTemplate: public IDCFieldDefinition, public IDCTemplate<IDCField>{

};

struct IDCField: public IDCObject, public IDCFieldDefinition{

};

enum FieldLock{ AlwaysLocked, AlwaysUnlocked, Locked, Unlocked };

struct IDCConfigFieldDefintiion: public IDCFieldDefinition{

};

struct IDCConfigField: public IDCField, public IDCConfigFieldDefintiion{
    
};

struct IDCConfigFieldTemplate: public IDCConfigFieldDefintiion, 
    public IDCTemplate<IDCConfigField>{

};

#pragma endregion IDC_Field

#pragma region IDCComponent

    enum DCComponentClass{
        DC_PROVIDER, DC_ACTUATOR,
        DC_MONITOR, DC_SINGLE,
        DC_NOMAND
    };  

    template<
        typename TInput, typename TOutput,
        typename TView, typename TField
    >
    struct IDCComponentDefition{

    };

    template<typename T>
    struct IDCComponentTemplate: IDCComponentDefition<
        IDCInputTemplate, IDCOutputTemplate,
        IDCViewTemplate, IDCFieldTemplate>{
            static_assert(std::is_base_of(T, IDCComponent));
    };

    struct IDCComponent: IDCObject,
    IDCComponentDefition<IDCInput, IDCOutput, IDCView, IDCField>{

    };

#pragma endregion

#pragma region IDC_Monitor

struct IDCMonitorDefinition: IDCObject{

};

struct IDCMonitor: IDCComponent, IDCMonitorDefinition{

};

struct IDCMonitorTemplate: IDCComponentTemplate<IDCMonitor>, 
    IDCMonitorDefinition{

};

#pragma endregion

#pragma region IDC_Provider

    struct IDCProviderDefinition: IDCObject{

    };

    struct IDCProvider: IDCComponent, IDCProviderDefinition{

    };

    struct IDCProviderTemplate: IDCComponentTemplate<IDCProvider>,
        IDCProviderDefinition{};

#pragma endregion

#pragma region IDC_Nodes

    struct IDCIONodeDefinition: IDCObject{

    };

    struct IDCInputDefinition: IDCIONodeDefinition{};
    struct IDCInput: IDCInputDefinition{};
    struct IDCInputTemplate: IDCTemplate<IDCInput>, IDCInputDefinition{};

    struct IDCViewDefinition: IDCInputDefinition{};
    struct IDCView: IDCViewDefinition{};
    struct IDCViewTemplate: IDCTemplate<IDCView>, IDCViewDefinition{};

    struct IDCOutputDefinition: IDCIONodeDefinition{};
    struct IDCOutput: IDCOutputDefinition{};
    struct IDCOutputTemplate: IDCTemplate<IDCOutput>, IDCOutputDefinition{};



#pragma endregion

#pragma region IDC_Link

#pragma endregion
