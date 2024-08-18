#include "dataman.h"
#include "maputil.h"

dataman::AppMemHandle::~AppMemHandle()
{
    _dm->freeAppMemory(this);
}

dataman::AppMemHandle::AppMemHandle(int appId, DataManager &dataManager):dcAppId(appId)
{
    _dm = &dataManager;
}
