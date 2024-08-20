#include "dc_file.h"

#include <algorithm>
#include <filesystem>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
const char *execPath()
{
    char buff[256];
    size_t len = sizeof(buff);
    int bytes = GetModuleFileName(NULL, buff, len);
    return bytes ? buff : nullptr;
}

#elif defined(PLATFORM_ANDROID)
#include <jni.h>
const char *execPath()
{
    jclass contextClass = env->GetObjectClass(context);
    jmethodID getPackageCodePath = env->GetMethodID(contextClass, "getPackageCodePath", "()Ljava/lang/String;");
    jstring codePath = (jstring)env->CallObjectMethod(context, getPackageCodePath);

    const char* pathChars = env->GetStringUTFChars(codePath, nullptr);
    std::string path(pathChars);
    env->ReleaseStringUTFChars(codePath, pathChars);
    return path.c_str();
}    
#elif defined(PLATFORM_GNU)
#include <unistd.h>
#include <limits>
const char* execPath(){
    
    char buff[1024] = "";
    auto len = readlink("/proc/self/exe", buff, 1024);
    
    return len >= 0 ? std::string(buff).c_str() : nullptr;
}
#endif

const char *absPath(const char *path)
{
    std::filesystem::path fsPath = path;



    return nullptr;
}

bool fileExists()
{
    return false;
}
bool dirExists()
{
    return false;
}

