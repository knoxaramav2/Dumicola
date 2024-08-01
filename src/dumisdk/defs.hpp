#pragma once
#include <stddef.h>
#include <string>
#include <cstdint>

typedef std::uintptr_t APPSID;
typedef size_t RSCID;

template<typename T> inline APPSID appId(T* ptr) { return reinterpret_cast<std::uintptr_t>(ptr); }
template<typename T> inline APPSID appId(T ptr) { return reinterpret_cast<std::uintptr_t>(&ptr); }

#define appId(ptr) reinterpret_cast<std::uintptr_t>(&ptr)
#define rscdId(name) std::hash<std::string>{}(std::string(name))

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