#include "dataman.hpp"
#include "maputil.hpp"

void dataman::DataManager::_loadDefaultTypes()
{
}

dataman::TypeConverter &dataman::DataManager::getConverter()
{
    return _converters;
}
