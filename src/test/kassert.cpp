#include "kassert.h"
#include "utils.h"
#include <stdio.h>
#include <string>

static std::vector<std::string> __errMsgs;
static bool __hasFail = false;

#define assertFailMsg(file, line) dcutil::frmstr("Assert fail: %s @ line: %d\n", file, line);

inline void __prntDbgAssert(const char* file, int line) { 
    #ifndef KASSERT_SILENT
    auto msg = assertFailMsg(file, line);
    printf("%s", msg.c_str());
    #endif
}

void KTEST::__assert(bool cond, const char * file, int line)
{
    if(!cond){
        __prntDbgAssert(file, line);
        exit(1);
    }
}

void KTEST::__assertLater(bool cond, const char * file, int line)
{
    if(cond){return;}
    auto msg = assertFailMsg(file, line);
    __hasFail |= !cond;
    __errMsgs.push_back(msg);
}

void KTEST::__applyAsserts()
{
    for(auto msg : __errMsgs){
        printf("%s", msg.c_str());
    }

    if(__hasFail){ exit(1); }
}

bool KTEST::__hasFailure()
{
    __applyAsserts();
    return __hasFail;
}

void KTEST::__assertThrows(std::function<void()> func, const char* file, int line)
{
    try{
        func();
        __assert(false, file, line);
    }catch(...){}
}

void KTEST::__assertNotThrows(std::function<void()> func, const char* file, int line)
{
    try{
        func();
    } catch (const std::exception& ex){
        printf("%s\r\n", ex.what());
        __assert(false, file, line);
    } catch(const std::string& ex){
        printf("%s\r\n", ex.c_str());
        __assert(false, file, line);
    }
    catch(...){
        __assert(false, file, line);
    }
}

void KTEST::__assertMultiple(
    const std::vector<std::function<bool()>> funcs, 
    const char * file, int line)
{
    bool err = false;

    for(auto fnc : funcs){
        bool fail = !fnc();
        if(fail) { __prntDbgAssert(file, line); }
        err |= fail;
    }

    if(err) { exit(1); }
}

void KTEST::__assertMultipleLater(
    const std::vector<std::function<bool()>> funcs, 
    const char * file, int line)
{
    for(auto fnc : funcs){
        bool fail = !fnc();
        if(!fail){continue;}
        auto msg = assertFailMsg(file, line);
        __hasFail |= fail;
        __errMsgs.push_back(msg);
    }
}