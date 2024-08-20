#include "libManager.h"

dumisdk::LibraryManager::LibraryManager()
{
}

const std::vector<dumisdk::Plugin> dumisdk::LibraryManager::listPlugins()
{
    std::vector<dumisdk::Plugin> ret;

    for(auto it = _plugins.begin(); it != _plugins.end(); ++it){
        ret.push_back(it->second);
    }

    return ret;
}

bool dumisdk::LibraryManager::refresh()
{
    return false;
}

bool dumisdk::LibraryManager::reload()
{
    return false;
}

bool dumisdk::LibraryManager::addPath(const char *path)
{
    std::string abspath{absPath(path)};

    for(std::filesystem::path pth : _paths){
        
    }

    return false;
}
