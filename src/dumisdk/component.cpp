#include "component.hpp"

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

// dumisdk::IONodeDefinition::IONodeDefinition(HASHID id, HASHID parentId, dumisdk::DCVar value)
//     :IDCDefinition(id, parentId),_value(value)
// {}

// dumisdk::IONodeDefinition::IONodeDefinition(dumisdk::DCVar value)
//     :IDCDefinition(0,0),_value(value)
// {
// }
