#pragma once
#include <stddef.h>
#include <string>
#include <cstdint>
#include "utils.hpp"

typedef std::uintptr_t APPSID;
typedef size_t RSCID;
typedef uint32_t HASHID;

//template<typename T> inline APPSID appId(T* ptr) { return reinterpret_cast<std::uintptr_t>(ptr); }
//template<typename T> inline APPSID appId(T ptr) { return reinterpret_cast<std::uintptr_t>(&ptr); }

//#define appId(ptr) reinterpret_cast<std::uintptr_t>(&ptr)
#define appId(ptr) reinterpret_cast<std::uintptr_t>(ptr)
#define rscdId(name) std::hash<std::string>{}(std::string(name))
#define hashId(name) dumisdk::FNV1A(name)

/* Environment Defs */
#if __GNUC__
#define PLATFORM_GNU
#if __x86_64__ || __ppc64__
#define ENV_64
#else
#define ENV_32
#endif

#elif _WIN32 || _WIN64
#define PLATFORM_WINDOWS
#if _WIN64
#define ENV_64
#else
#define ENV_32
#endif

#else
#error "Unsupported OS or configuration"
#endif

#ifdef ENV_64
#define BITMODE 64
#else
#define BITMODE 32
#endif

#define DC_BOOL "__DC_IT_BOOL"
#define DC_INTEGER "__DC_IT_INTEGER"
#define DC_DECIMAL "__DC_IT_DECIMAL"
#define DC_STRING "__DC_IT_STRING"
#define DC_MAP "__DC_IT_MAP"
#define DC_LIST "__DC_IT_LIST"



