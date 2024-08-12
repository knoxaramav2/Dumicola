#include "dtypes.hpp"
#include "defs.hpp"

#pragma region IDC_Basic

/// @brief Common component/template data
struct IDCBase{
    HASHID id;
    HASHID parentId;
    virtual ~IDCBase() = default;
};

/* Forward declares */
struct IDCInput; struct IDCInputTemplate;
struct IDCOutput; struct IDCOutputTemplate;
struct IDCField; struct IDCFieldTemplate;
struct IDCView; struct IDCViewTemplate;
struct IDCComponent; template<typename T> struct IDCComponentTemplate;


struct IDCObject: public virtual IDCBase{
    virtual ~IDCObject() = default;
};

/// @brief Base template interface
/// @tparam T Type of component
template<typename T>
struct IDCTemplate: public virtual IDCBase{
    virtual T* createInstance() = 0;
    virtual ~IDCTemplate() = default;
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
    
    HASHID id;
    //const std::vector<IDCComponentTemplate<IDCComponent>> getComponents();
    virtual IDCComponent* getComponent() = 0;
    virtual ~IDCLibrary() = default;
};

#pragma endregion IDC_Library

#pragma region IDC_Field

struct IDCFieldDefinition: public virtual IDCBase{
    bool visible;

    ~IDCFieldDefinition() = default;
};

struct IDCFieldTemplate: public virtual IDCFieldDefinition, 
    public virtual IDCTemplate<IDCField>{
    ~IDCFieldTemplate() = default;
};

struct IDCField: public virtual IDCObject, public virtual IDCFieldDefinition{
    ~IDCField() = default;
    virtual void Set() = 0;
};

enum FieldLock{ AlwaysLocked, AlwaysUnlocked, Locked, Unlocked };

struct IDCConfigFieldDefintiion: public virtual IDCFieldDefinition{
    ~IDCConfigFieldDefintiion() = default;
};

struct IDCConfigField: public virtual IDCField, public virtual IDCConfigFieldDefintiion{
    ~IDCConfigField() = default;
};

struct IDCConfigFieldTemplate: public virtual IDCConfigFieldDefintiion, 
    public virtual IDCTemplate<IDCConfigField>{
    ~IDCConfigFieldTemplate() = default;
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
        typename TView, typename TField>
    struct IDCComponentDefition{
        ~IDCComponentDefition() = default;
    };

    template<typename T>
    struct IDCComponentTemplate: IDCComponentDefition<
        IDCInputTemplate, IDCOutputTemplate,
        IDCViewTemplate, IDCFieldTemplate>{
        ~IDCComponentTemplate() = default;
    };

    struct IDCComponent: IDCObject,
    IDCComponentDefition<IDCInput, IDCOutput, IDCView, IDCField>{
        ~IDCComponent() = default;
    };

#pragma endregion

#pragma region IDC_Monitor

struct IDCMonitorDefinition: public virtual IDCObject{
    ~IDCMonitorDefinition() = default;
};

struct IDCMonitor: public virtual IDCComponent, public virtual IDCMonitorDefinition{
    ~IDCMonitor() = default;
};

struct IDCMonitorTemplate: public virtual IDCComponentTemplate<IDCMonitor>, 
    public virtual IDCMonitorDefinition{
    ~IDCMonitorTemplate() = default;
};

#pragma endregion

#pragma region IDC_Provider

    struct IDCProviderDefinition: public virtual IDCObject{
        ~IDCProviderDefinition() = default;
    };

    struct IDCProvider: public virtual IDCComponent, public virtual IDCProviderDefinition{
        ~IDCProvider() = default;
    };

    struct IDCProviderTemplate: public virtual IDCComponentTemplate<IDCProvider>,
        public virtual IDCProviderDefinition{
        ~IDCProviderTemplate() = default;
    };

#pragma endregion

#pragma region IDC_Nodes

    struct IDCIONodeDefinition: public virtual IDCObject{
        ~IDCIONodeDefinition() = default;
    };

    struct IDCInputDefinition: public virtual IDCIONodeDefinition{
        ~IDCInputDefinition() = default;
    };
    struct IDCInput: public virtual IDCInputDefinition{
        ~IDCInput() = default;
    };
    struct IDCInputTemplate: 
        public virtual IDCTemplate<IDCInput>, public virtual IDCInputDefinition{
        ~IDCInputTemplate() = default;
    };

    struct IDCViewDefinition: public virtual IDCInputDefinition{
        ~IDCViewDefinition() = default;
    };
    struct IDCView: public virtual IDCViewDefinition{
        ~IDCView() = default;
    };
    struct IDCViewTemplate: 
        public virtual IDCTemplate<IDCView>, public virtual IDCViewDefinition{
        ~IDCViewTemplate() = default;
    };

    struct IDCOutputDefinition: public virtual IDCIONodeDefinition{
        ~IDCOutputDefinition() = default;
    };
    struct IDCOutput: public virtual IDCOutputDefinition{
        ~IDCOutput() = default;
    };
    struct IDCOutputTemplate: 
        public virtual IDCTemplate<IDCOutput>, public virtual IDCOutputDefinition{
        ~IDCOutputTemplate() = default;
    };

#pragma endregion

#pragma region IDC_Link

#pragma endregion
