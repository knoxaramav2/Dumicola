#pragma once

#include <filesystem>

std::filesystem::path execPath();
std::filesystem::path rootDir();
std::filesystem::path sdlDir();
bool fileExists(std::string path);
bool fileExists(std::filesystem::path path);
bool dirExists(std::string path);
bool dirExists(std::filesystem::path path);
bool pathExists(std::string path);
bool pathExists(std::filesystem::path path);
