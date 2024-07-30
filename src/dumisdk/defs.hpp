#pragma once
#include <stddef.h>
#include <string>
#include <cstdint>

typedef std::uintptr_t APPSID;
typedef size_t RSCID;


template<typename T> inline APPSID appId(T* ptr) { return reinterpret_cast<std::uintptr_t>(ptr); }
template<typename T> inline APPSID appId(T ptr) { return reinterpret_cast<std::uintptr_t>(&ptr); }

#define appId(ptr) reinterpret_cast<std::uintptr_t>(&ptr);
#define rscdId(name) std::hash<std::string>{}(std::string(name));

