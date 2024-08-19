
#include <memory>

#include "component.h"

dumisdk::DCDefinition::DCDefinition(HASHID id, HASHID parentId):
    id(id), parentId(parentId) {}

dumisdk::DCImplementation::DCImplementation(HASHID id, HASHID parentId):
    DCDefinition(id, parentId) {}

dumisdk::DCComponentDefinition::DCComponentDefinition(HASHID id, HASHID parentId):
    DCDefinition(id, parentId) {}




dumisdk::ComponentInfo::ComponentInfo(const char *name, const char *description):
    name(name),componentId(componentId),description(description) {}

// dumisdk::IDCLibrary::IDCLibrary(const char *name, const char *version, const char *author, 
//     const char *repository, const char *description):
//     name(name),version(version),author(author),repository(repository),
//     description(description),libraryId(appId(this)) {}

const dumisdk::DCComponentImplementation *dumisdk::IDCLibrary::create(const char *name)
{
    return create(hashId(name));
}

const dumisdk::DCComponentImplementation *dumisdk::IDCLibrary::create(HASHID id)
{
    auto it = _templates.find(id);
    if(it == _templates.end()){ return nullptr; }
    return it->second->create();
}

dumisdk::IDCLibrary::IDCLibrary(const char *name, const char *version, const char *author,
                                const char *repository, const char *description) : name(name), version(version), author(author), repository(repository),
                                                                                   description(description), libraryId(appId(this)) {}

