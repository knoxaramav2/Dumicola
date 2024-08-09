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
}

#define assert(cond) KTEST::__assert(cond, __FILE__, __LINE__)
#define assertLater(cond) KTEST::__assertLater(cond, __FILE__, __LINE__)
#define applyAsserts() KTEST::__applyAsserts()
#define assertMultiple(funcs) KTEST::__assertMultiple(funcs, __FILE__, __LINE__)
#define assertMultipleLater(funcs) KTEST::__assertMultipleLater(funcs, __FILE__, __LINE__)
#define testsFailed KTEST::__hasFailure()
#define assertThrows(expr) try { (expr); KTEST::__assert(false, __FILE__, __LINE__); } catch (...) {}
#define assertNotThrows(expr) try{ (expr); } catch (...) {KTEST::__assert(false, __FILE__, __LINE__); }
