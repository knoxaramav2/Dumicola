#pragma once
#include <stddef.h>
#include <string>
#include <cstdint>
#include "id.hpp"
#include "platform.hpp"

typedef std::uintptr_t APPSID;
typedef size_t RSCID;
typedef uint32_t HASHID;

//#define appId(ptr) reinterpret_cast<std::uintptr_t>(&ptr)
#define appId(ptr) reinterpret_cast<std::uintptr_t>(ptr)
#define rscdId(name) std::hash<std::string>{}(std::string(name))
#define hashId(name) FNV1A(name)

#define DC_BOOL "__DC_IT_BOOL"
#define DC_INTEGER "__DC_IT_INTEGER"
#define DC_DECIMAL "__DC_IT_DECIMAL"
#define DC_STRING "__DC_IT_STRING"
#define DC_MAP "__DC_IT_MAP"
#define DC_LIST "__DC_IT_LIST"



