#pragma once

#define TEST PLATFORM

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

#elif _ANDROID
	#define PLATFORM_ANDROID
#if _ANDROID64
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

#ifdef PLATFORM_WINDOWS
	#define NL "\r\n"
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif defined(PLATFORM_GNU)
	#define NL "\n"
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#elif defined(PLATFORM_ANDROID)
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#endif

#define BUILD_CONFIG Debug

#if Debug == Debug
	#define DEBUG_MODE
#endif

//#define BUILD_CONFIG Debug
