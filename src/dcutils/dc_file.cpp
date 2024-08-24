#include "dc_file.h"
#include "dc_string.h"
#include "environment.h"

#include <algorithm>
#include <sys/stat.h>
#include <fstream>

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
fs::path dcutil::execPath(){
    
    char buff[1024] = "";
    auto len = readlink("/proc/self/exe", buff, 1024);
    
    std::string path = len >= 0 ? std::string(buff) : "";
    return fs::path(path);
}
#endif

struct stat sb;

fs::path dcutil::rootDir()
{
    fs::path path(execPath());
    path = path.parent_path().parent_path();
    return path;
}

fs::path dcutil::sdlDir()
{
    auto path = rootDir()/"dcstl";
    return path;
}

bool dcutil::fileExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR));
}

bool dcutil::fileExists(std::filesystem::path path)
{
    return fileExists(path.string());
}

bool dcutil::dirExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR));
}

bool dcutil::dirExists(std::filesystem::path path)
{
    return dirExists(path.string());
}

bool dcutil::pathExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0);
}

bool dcutil::pathExists(std::filesystem::path path)
{
    return pathExists(path.string());
}

std::vector<std::filesystem::path> dcutil::listFiles(std::filesystem::path path, std::string extFilter, bool recursive)
{
    auto extensions = dcutil::split(extFilter, ";");
    std::vector<std::filesystem::path> ret;
    for(const auto& item: std::filesystem::directory_iterator(path)){
        if(item.is_directory()){
            if(!recursive){continue;}
            auto subPaths = listFiles(item.path(), extFilter, true);
            ret.insert(ret.end(), subPaths.begin(), subPaths.end());
        } else {
            auto ext = path.extension().string();
            for(auto& e: extensions){
                if(dcutil::strEquals(ext, e, true)){
                    ret.push_back(path);
                    break;
                }
            }
        }
    }

    return ret;
}

std::string dcutil::readFileAsString(std::filesystem::path path){

}

std::vector<std::filesystem::path> dcutil::listFiles(std::filesystem::path path, 
    const char* extFilter, bool recursive){

    
    
}