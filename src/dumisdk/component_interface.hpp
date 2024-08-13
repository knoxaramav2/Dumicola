#include "dtypes.hpp"
#include "defs.hpp"
#include "dumiexcept.hpp"

#include <memory>
#include <exception>

#pragma region IDC_Basic

struct DCDefinition{
    HASHID id;
    HASHID parentId;
    const char* name;
    DCDefinition(const char* name, HASHID parentId=0);
    protected:
    DCDefinition():DCDefinition("",0){}
};

struct IDCImplement: public virtual DCDefinition{
    IDCImplement(const char* name, HASHID parentId=0):
        DCDefinition(name, parentId){};
    protected:
    IDCImplement(){};
};

template<typename T>
struct IDCTemplate: public virtual DCDefinition{
    IDCTemplate(const char* name, HASHID parentId): DCDefinition(name, parentId){}
    static_assert(std::is_base_of<IDCImplement, T>::value);
    virtual std::shared_ptr<T> create() = 0;
    protected:
    IDCTemplate(){}
};

#pragma endregion

#pragma region IDC_Library

struct DCComponent;
template<typename T> struct DCComponentTemplate;

struct IDCLibrary{
    const char* name;
    const char* version;
    const char* author;
    const char* repository;
    const char* description;

    virtual ~IDCLibrary() = default;

    virtual const std::vector<DCDefinition> GetComponents() = 0;
    virtual const DCDefinition& GetComponent(HASHID id) = 0;
};

#pragma endregion 

#pragma region IDC_Field

struct DCFieldDefinition: public virtual DCDefinition{
    DCFieldDefinition(const char* name, HASHID parentId):DCDefinition(name, parentId){};

    protected:
    DCFieldDefinition(){}
    std::shared_ptr<dumisdk::DCVar> _value;
};

struct IDCField: public virtual DCFieldDefinition, public virtual IDCImplement{
    IDCField(const char* name, HASHID parentId):DCDefinition(name, parentId){};
    virtual void set(std::shared_ptr<dumisdk::DCVar> value);
    virtual std::shared_ptr<dumisdk::DCVar> get();
    protected:
    IDCField(){};
};

struct DCFieldTemplate: 
    public virtual DCFieldDefinition, public virtual IDCTemplate<IDCField>{
    DCFieldTemplate(const char* name, HASHID parentId):DCDefinition(name, parentId){};
    protected:
    DCFieldTemplate(){};
};

enum EditLock{
    FIELDLOCK_NEVER, FIELDLOCK_ALWAYS,  
    FIELDLOCK_UNLOCKED, FIELDLOCK_LOCKED,
};
#define FieldlockToggleable(lock) (lock & 2)

struct DCConfigFieldDefinition: public virtual DCFieldDefinition{
    DCConfigFieldDefinition(const char* name, HASHID parentId): 
        DCDefinition(name, parentId){};
    protected:
    DCConfigFieldDefinition(){}
};

struct DCConfigField: public virtual IDCField, public virtual DCConfigFieldDefinition{
    DCConfigField(const char* name, HASHID parentId):DCDefinition(name, parentId){};
    protected:
    DCConfigField(){}
};

struct DCConfigFieldTemplate: public virtual DCFieldTemplate, public virtual DCConfigFieldDefinition{
    DCConfigFieldTemplate(const char* name, HASHID parentId):DCDefinition(name, parentId){};
    protected:
    DCConfigFieldTemplate(){}
};

#pragma endregion

#pragma region IDCComponent

#pragma endregion

#pragma region IDC_Monitor


#pragma endregion

#pragma region IDC_Provider


#pragma endregion

#pragma region IDC_Nodes

#pragma endregion

#pragma region IDC_Link

#pragma endregion

#pragma region IDC_Application


#pragma endregion
