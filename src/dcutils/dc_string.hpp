#pragma once

#include <string>
#include <memory>

template<typename... Args>
std::string frmstr(const char* f_str, Args ... args){
    int size_sn = std::snprintf(nullptr, 0, f_str, args ...);
    if(size_sn <= 0) { return ""; }
    auto size = static_cast<size_t>(size_sn);
    std::unique_ptr<char[]> buf(new char[size]);
    auto buf_ls = buf.get();
    std::snprintf(buf_ls, size, f_str, args ...);
    return std::string(buf_ls, buf_ls + size - 1);
}

template<typename... Args>
std::string frmstr(const std::string& f_str, Args ... args){
    return frmstr(f_str.c_str(), args...);
}