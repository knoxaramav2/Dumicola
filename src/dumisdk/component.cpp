
#include <memory>

#include "component.h"

dumisdk::DCDefinition::DCDefinition(DCDefinition& definition) :
	id(definition.id), parentId(definition.parentId) {}

dumisdk::DCDefinition::DCDefinition(HASHID id, HASHID parentId) : id(id), parentId(parentId) {}

dumisdk::DCDefinition::DCDefinition() :id(0), parentId(0) {}

dumisdk::DCImplementation::DCImplementation(HASHID id, HASHID parentId) :
	DCDefinition(id, parentId) {}

dumisdk::DCImplementation::DCImplementation() {}

dumisdk::DCComponentDefinition::DCComponentDefinition(HASHID id, HASHID parentId, 
	DCFieldDefinition* fields) :
	DCDefinition(id, parentId), fields(fields) {}

dumisdk::DCComponentDefinition::DCComponentDefinition() {}

const dumisdk::DCComponentImplementation* dumisdk::IDCLibrary::create(const char* name)
{
	return create(hashId(name));
}

const dumisdk::DCComponentImplementation* dumisdk::IDCLibrary::create(HASHID id)
{
	auto it = _templates.find(id);
	if (it == _templates.end()) { return nullptr; }
	return it->second->create();
}

dumisdk::IDCLibrary::IDCLibrary(const char* name, const char* version, const char* author,
	const char* repository, const char* description) :
	LibraryInfo(name, version, author, repository, description, appId(this)) {}

dumisdk::DCComponentImplementation::DCComponentImplementation() {}

dumisdk::DCComponentImplementation::DCComponentImplementation(DCComponentDefinition& definition) :
	DCComponentDefinition(definition), DCDefinition(definition), DCImplementation(definition.id, definition.parentId)
{
}

dumisdk::LibraryInfo::LibraryInfo(const char* name, const char* version, const char* author,
	const char* repository, const char* description, APPSID libraryId) :
	name(name), version(version), author(author), repository(repository), description(description),
	libraryId(libraryId) {}

dumisdk::ComponentInfo::ComponentInfo(const char* name, const char* description, APPSID libraryId):
	name(name), description(description), libraryId(libraryId){}
