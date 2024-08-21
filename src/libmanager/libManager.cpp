#include "libManager.h"
#include "dc_string.h"
#include "dc_file.h"

#include <cstdio>

std::vector<std::filesystem::path> dumisdk::LibraryManager::_dllPaths()
{
    std::vector<std::filesystem::path> ret;
    for(auto& path: _paths){
        auto pstr = path.string();
        printf("Searching %s....\r\n", pstr.c_str());
        if(!dirExists(pstr)){
            printf("\tSkipping %s\r\n", pstr.c_str());
            continue;
        }
        for(const auto& file : std::filesystem::directory_iterator(path)){
            printf("Found %s:    DLL? ", file.path().string().c_str());
            bool isDll = dcutil::strEquals(file.path().extension().string(), ".dll", true);
            printf("%d\r\n", isDll);
            if(isDll){
                ret.push_back(file);
            }
            //file.path().extension();
        }
    }

    return ret;
}

dumisdk::LibraryManager::LibraryManager()
{
    std::filesystem::path xpath(execPath());
    _paths.push_back(xpath);
    _paths.push_back(xpath/"plugins");
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

bool dumisdk::LibraryManager::load()
{
    auto dllPaths = _dllPaths();
    return false;
}

bool dumisdk::LibraryManager::addPath(const char *path)
{
    auto absPath = std::filesystem::absolute(path);

    for(const auto& p: _paths){
        if(p == absPath){ return false; }
    }

    _paths.push_back(absPath);
    return true;
}
