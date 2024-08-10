#include "dc_string.hpp"

#include <string>
#include <memory>
#include <cstdarg>
#include <vector>

std::string frmstr(const char* f_str, ...){
    va_list args;
    va_start(args, f_str);
    va_list args_copy;
    va_copy(args_copy, args);
    const int size = std::vsnprintf(nullptr, 0, f_str, args_copy);
    va_end(args_copy);
    std::unique_ptr<char[]> buffer(new char[size]);
    std::vsnprintf(buffer.get(), size+1, f_str, args);
    va_end(args);
    return std::string(buffer.get(), size);
}

const char* testStr(){
    return "Hello";
}