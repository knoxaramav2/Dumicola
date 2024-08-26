#include "dc_string.h"

#include <memory>
#include <cstdarg>
#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>

std::string dcutil::frmstr(const char* f_str, ...){
    va_list args;
    va_start(args, f_str);
    va_list args_copy;
    va_copy(args_copy, args);
    const int size = std::vsnprintf(nullptr, 0, f_str, args_copy);
    va_end(args_copy);
    std::unique_ptr<char[]> buffer(new char[size+1]);
    std::vsnprintf(buffer.get(), size+1, f_str, args);
    va_end(args);
    return std::string(buffer.get(), size);
}

std::string dcutil::toLower(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c){return std::tolower(c);});
    return value;
}

const char *dcutil::toLower(const char *value)
{
    return toLower(std::string(value)).c_str();
}

std::string dcutil::toUpper(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c){return std::toupper(c);});
    return value;
}

const char *dcutil::toUpper(const char *value)
{
    return toUpper(std::string(value)).c_str();
}

bool dcutil::strEquals(std::string lstr, std::string rstr, bool ignoreCase)
{
    if(ignoreCase){
        std::string lu = toUpper(lstr);
        std::string ru = toUpper(rstr);
        return lu == ru;
    }

    return lstr == rstr;
}

std::vector<std::string> dcutil::split(std::string text, const char* delim)
{
    std::stringstream ss(text);
    size_t prev = 0, pos;
    std::vector<std::string> terms;
    while((pos = text.find_first_of(delim, prev)) != std::string::npos){
        if(pos > prev){
            terms.push_back(text.substr(prev, pos-prev));
            prev = pos + 1;
        }
        if(prev < text.length()){
            terms.push_back(text.substr(prev, std::string::npos));
        }
    }

    return terms;
}
