#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "defs.h"
#include "dc_file.h"

namespace dumisdk{
    struct Plugin{

    };

    class LibraryManager{

        optmap<HASHID, Plugin> _plugins;
        std::vector<std::filesystem::path> _paths;

        public:

        LibraryManager();

        const std::vector<Plugin> listPlugins();
        bool refresh();
        bool reload();
        bool addPath(const char* path);

    };
}


