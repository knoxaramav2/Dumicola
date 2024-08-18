#include "component.h"

dumisdk::IDCDefinition::IDCDefinition(HASHID id , HASHID parentId):
    id(id),parentId(parentId)
{}

dumisdk::IDCImplementation::IDCImplementation(HASHID id, HASHID parentId)
    :IDCDefinition(id, parentId)
{
}

dumisdk::IDCImplementation::IDCImplementation(): IDCDefinition(0,0)
{
}

dumisdk::DCComponentDefinition::DCComponentDefinition(HASHID id, HASHID parentId)
    :IDCDefinition(id, parentId)
{
}

dumisdk::DCComponentDefinition::DCComponentDefinition()
    :IDCDefinition(0, 0)
{
}

dumisdk::IDCLibrary::IDCLibrary(
    const char* name, const char* version, const char* author, 
    const char* repository):
    libraryId(appId(this)),name(name),version(version),author(author),repository(repository)
{
    
}
