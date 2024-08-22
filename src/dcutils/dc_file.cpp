#include "dc_file.h"
#include "environment.h"

#include <algorithm>
#include <sys/stat.h>

namespace fs = std::filesystem;

#ifdef PLATFORM_WINDOWS
#include <windows.h>
fs::path execPath()
{
    char buff[256];
    size_t len = sizeof(buff);
    int bytes = GetModuleFileName(NULL, buff, len);
    if(bytes >= 0){
        return std::filesystem::path(buff).parent_path();
    } else {
        return "";
    }
}

#elif defined(PLATFORM_ANDROID)
#include <jni.h>
// const char *execPath()
// {
//     jclass contextClass = env->GetObjectClass(context);
//     jmethodID getPackageCodePath = env->GetMethodID(contextClass, "getPackageCodePath", "()Ljava/lang/String;");
//     jstring codePath = (jstring)env->CallObjectMethod(context, getPackageCodePath);

//     const char* pathChars = env->GetStringUTFChars(codePath, nullptr);
//     std::string path(pathChars);
//     env->ReleaseStringUTFChars(codePath, pathChars);
//     return path.c_str();
// }    
#elif defined(PLATFORM_GNU)
#include <unistd.h>
#include <limits>
fs::path execPath(){
    
    char buff[1024] = "";
    auto len = readlink("/proc/self/exe", buff, 1024);
    
    std::string path = len >= 0 ? std::string(buff) : "";
    return fs::path(path);
}
#endif

struct stat sb;

fs::path rootDir()
{
    fs::path path(execPath());
    path = path.parent_path().parent_path();
    return path;
}

fs::path sdlDir()
{
    auto path = rootDir()/"dcstl";
    return path;
}

bool fileExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR));
}

bool fileExists(std::filesystem::path path)
{
    return fileExists(path.string());
}

bool dirExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR));
}

bool dirExists(std::filesystem::path path)
{
    return dirExists(path.string());
}

bool pathExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0);
}

bool pathExists(std::filesystem::path path)
{
    return pathExists(path.string());
}

