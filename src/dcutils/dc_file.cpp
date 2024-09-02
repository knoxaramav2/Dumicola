#include "dc_file.h"
#include "dc_string.h"
#include "environment.h"

#include <algorithm>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

#ifdef PLATFORM_WINDOWS
#include <windows.h>
fs::path dcutil::execPath()
{
    char buff[256];
    size_t len = sizeof(buff);
    int bytes = GetModuleFileName(NULL, buff, len);
    if(bytes >= 0){
        return fs::path(buff).parent_path();
    } else {
        return "";
    }
}

#elif defined(PLATFORM_ANDROID)
#include <jni.h>
fs::path dcutil::execPath()
{
    jclass contextClass = env->GetObjectClass(context);
    jmethodID getPackageCodePath = env->GetMethodID(contextClass, "getPackageCodePath", "()Ljava/lang/String;");
    jstring codePath = (jstring)env->CallObjectMethod(context, getPackageCodePath);

    const char* pathChars = env->GetStringUTFChars(codePath, nullptr);
    std::string path(pathChars);
    env->ReleaseStringUTFChars(codePath, pathChars);
    return fs::path{path};
}    
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

fs::path dcutil::rootDir()
{
    fs::path path(execPath());
    path = path.parent_path();
    return path;
}

fs::path dcutil::sdlDir()
{
    auto path = rootDir()/"dcstl";
    return path;
}

struct stat sb;
bool dcutil::fileExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR));
}

bool dcutil::fileExists(fs::path path)
{
    return fileExists(path.string());
}

bool dcutil::dirExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR));
}

bool dcutil::dirExists(fs::path path)
{
    return dirExists(path.string());
}

bool dcutil::pathExists(std::string path)
{
    return (stat(path.c_str(), &sb) == 0);
}

bool dcutil::pathExists(fs::path path)
{
    return pathExists(path.string());
}

std::vector<fs::path> dcutil::listFiles(fs::path path, const char* extFilter, bool recursive)
{
    auto extensions = dcutil::split(extFilter, ";");
    std::vector<fs::path> ret;
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

std::string dcutil::readFileAsString(fs::path path){

    std::ifstream fs(path);

    if(!(fs.is_open() && fs.good())){ 
        return "";
    }

    std::stringstream ss;
    ss << fs.rdbuf();
    return ss.str();
}

bool dcutil::writeFile(fs::path path, std::string &data, bool append)
{
    auto flag = (append ? std::ios::app : std::ios::trunc) | std::ios::out;
    std::ofstream fs(path, flag);
    if(!(fs.is_open() && fs.good())){ 
        return false;
    }

    fs << data;

    return true;
}

std::vector<std::string> readFileByLines(fs::path path){
    std::vector<std::string> ret;
    std::ifstream fs(path);

    if(!(fs.is_open() && fs.good())){ 
        return {};
    }

    std::string line;
    while(getline(fs, line)){
        ret.push_back(line);
    }

    return ret;
}

bool dcutil::writeFile(fs::path path, std::vector<std::string> &data, bool append)
{
    auto flag = (append ? std::ios::app : std::ios::trunc) | std::ios::out;
    std::ofstream fs(path, flag);
    if(!(fs.is_open() && fs.good())){ 
        return false;
    }

    for(auto&line:data){ fs << line << NL; }
    fs.close();

    return false;
}
