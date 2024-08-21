#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "defs.h"
#include "dc_file.h"
#include "component.h"

namespace dumisdk{
    struct Plugin{
        std::filesystem::path path;
        std::string name;
        dumisdk::IDCLibrary* library;
    };

    class LibraryManager{

        optmap<HASHID, Plugin> _plugins;
        std::vector<std::filesystem::path> _paths;
        std::vector<std::filesystem::path> _dllPaths();

        public:

        LibraryManager();

        const std::vector<Plugin> listPlugins();
        bool refresh();
        bool load();
        bool addPath(const char* path);

    };
}


