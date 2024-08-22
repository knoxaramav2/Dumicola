#include "libManager.h"
#include "dc_string.h"
#include "dc_file.h"
#include "environment.h"

#include <cstdio>
#include <type_traits>

#ifdef PLATFORM_WINDOWS
#include<Windows.h>
#elif(defined(PLATFORM_GNU))
#include <dlfcn.h>
#elif(defined(PLATFORM_ANDROID))
#error Android component support not implemented
#endif

dumisdk::Plugin::Plugin(std::filesystem::path path, dumisdk::IDCLibrary *library):
    path{path}, name{library->name}, library{library}, id{hashId(name)} {}

std::vector<std::filesystem::path> dumisdk::LibraryManager::_findSharedLibs()
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
            auto ext = file.path().extension().string();
            bool isLib = dcutil::strEquals(ext, ".dll", true) || dcutil::strEquals(ext, ".so", true);
            if(isLib){
                ret.push_back(file);
            }
        }
    }

    return ret;
}

dumisdk::IDCLibrary* dumisdk::LibraryManager::_tryLoadLibrary(std::string path)
{
    dumisdk::IDCLibrary* ret = nullptr;
    using LLF = dumisdk::IDCLibrary* (*)();

#ifdef PLATFORM_WINDOWS
    HMODULE hmdl = LoadLibrary(path.c_str());
    if(!hmdl){ return nullptr; }
    LLF libload = (LLF)GetProcAddress(hmdl, "LoadLibrary");
    if(!libload){
        printf("\tCandidate %s not loaded%s", path.c_str(), NL);
        FreeLibrary(hmdl);
        return nullptr;
    }
    ret = libload();
    if(!ret){ 
        printf("\tCandidate %s lacks load method %s", path.c_str(), NL);
        FreeLibrary(hmdl); 
    }
#elif(defined(PLATFORM_GNU))
    void* hndl = dlopen(libPath.c_str(), RTLD_LAZY);
    if(!hndl){return nullptr;}
    LLF libload = (LLF)dlsym(hndl, "LoadLibrary");
    if(!libload){
        dlclose(hndl);
        return nullptr;
    }
    ret = libload();
    if(!ret){ dlclose(hndl); }
#elif(defined(PLATFORM_ANDROID))

#endif

    return ret;
}

void dumisdk::LibraryManager::_filterSharedLibs(std::vector<std::filesystem::path>& paths)
{
    for(auto it = paths.begin(); it != paths.end(); ++it){
        for(auto& plugin: _plugins){
            if(plugin.second.path == *it)
            { 
                paths.erase(it);
                --it;
                break; 
            }
        }
    }
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
    _paths.clear();
    return false;
}

bool dumisdk::LibraryManager::load()
{
    auto cmpPaths = _findSharedLibs();
    _filterSharedLibs(cmpPaths);

    for(auto& path:cmpPaths){
        auto library = _tryLoadLibrary(path.string());
        if(library){
            Plugin p{path, library};
            _plugins.emplace(p.id, std::move(p));
            printf(">> Imported library %s%s", p.name, NL);
        }
    }

    return true;
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
