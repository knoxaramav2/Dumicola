#include "dataman.hpp"
#include "maputil.hpp"

dataman::TypeConverter &dataman::DataManager::getConverter()
{
    return _converters;
}
