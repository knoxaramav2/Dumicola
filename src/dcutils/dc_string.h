#pragma once

#include <string>
#include <vector>

namespace dcutil{
    std::string frmstr(const char* f_str, ...);
    std::string toLower(std::string value);
    const char* toLower(const char* value);
    std::string toUpper(std::string value);
    const char* toUpper(const char* value);
    bool strEquals(std::string lstr, std::string rstr, bool ignoreCase=false);
    std::vector<std::string> split(std::string text, const char* delim);
}
