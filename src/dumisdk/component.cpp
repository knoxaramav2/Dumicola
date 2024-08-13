#include "component.hpp"

DCDefinition::DCDefinition(const char* name, HASHID parentId){
    this->name = name;
    this->parentId = parentId;
    this->id = FNV1A(name);
}

void IDCField::set(std::shared_ptr<dumisdk::DCVar> value)
{
    _value = value;
}

std::shared_ptr<dumisdk::DCVar> IDCField::get()
{
    return _value;
}

