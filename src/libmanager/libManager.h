#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "defs.h"
#include "dc_file.h"
#include "component.h"

namespace dumisdk{
    struct Plugin{
        const std::filesystem::path path;
        const char* name;
        const HASHID id;
        const dumisdk::IDCLibrary* library;
        Plugin(std::filesystem::path path, dumisdk::IDCLibrary* library);
    };

    class LibraryManager{

        optmap<HASHID, Plugin> _plugins;
        std::vector<std::filesystem::path> _paths;
        std::vector<std::filesystem::path> _findSharedLibs();
        dumisdk::IDCLibrary* _tryLoadLibrary(std::string path);
        void _filterSharedLibs(std::vector<std::filesystem::path>& paths);

        public:

        LibraryManager();

        const std::vector<Plugin> listPlugins();
        bool refresh();
        bool load();
        bool addPath(const char* path);

    };
}


