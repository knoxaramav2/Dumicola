#pragma once

#include<vector>
#include<functional>
#include<exception>

namespace KTEST
{
    void __assert(bool cond, const char* file, int line);
    void __assertLater(bool cond, const char* file, int line);
    void __assertMultiple(const std::vector<std::function<bool()>> funcs, const char* file, int line);
    void __assertMultipleLater(const std::vector<std::function<bool()>> funcs, const char* file, int line);
    void __applyAsserts();
    bool __hasFailure();
    void __assertThrows(std::function<void()> func, const char* file, int line);
    void __assertNotThrows(std::function<void()> func, const char* file, int line);
}

#define assert(cond) KTEST::__assert(cond, __FILE__, __LINE__)
#define assertLater(cond) KTEST::__assertLater(cond, __FILE__, __LINE__)
#define applyAsserts() KTEST::__applyAsserts()
#define assertMultiple(funcs) KTEST::__assertMultiple(funcs, __FILE__, __LINE__)
#define assertMultipleLater(funcs) KTEST::__assertMultipleLater(funcs, __FILE__, __LINE__)
#define testsFailed KTEST::__hasFailure()
#define assertThrows(expr) KTEST::__assertThrows(expr, __FILE__, __LINE__)
#define assertNotThrows(expr) KTEST::__assertNotThrows(expr, __FILE__, __LINE__)
//#define assertThrows(expr) try { (expr); KTEST::__assert(true, __FILE__, __LINE__); } catch (...) {}
//#define assertNotThrows(expr) try{ expr; } catch (...) {KTEST::__assert(false, __FILE__, __LINE__); }
