#include "component.hpp"

dumisdk::IDCCompDef::IDCCompDef(HASHID id , HASHID parentId):
    id(id),parentId(parentId)
{}

dumisdk::IDCComp::IDCComp(HASHID id, HASHID parentId)
    :IDCCompDef(id, parentId)
{
}

dumisdk::IDCComp::IDCComp(): IDCCompDef(0,0)
{
}
