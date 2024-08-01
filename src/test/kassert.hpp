#pragma once

#include<vector>
#include<functional>

namespace KTEST
{
    void __assert(bool cond, const char* file, int line);
    void __assertLater(bool cond, const char* file, int line);
    void __assertMultiple(const std::vector<std::function<bool()>> funcs, const char* file, int line);
    void __assertMultipleLater(const std::vector<std::function<bool()>> funcs, const char* file, int line);
    void __applyAsserts();

    #define assert(cond) __assert(cond, __FILE__, __LINE__)
    #define assertLater(cond) __assertLater(cond, __FILE__, __LINE__)
    #define applyAsserts() __applyAsserts()
    #define assertMultiple(funcs) __assertMultiple(funcs, __FILE__, __LINE__)
    #define assertMultipleLater(funcs) __assertMultipleLater(funcs, __FILE__, __LINE__)
}
