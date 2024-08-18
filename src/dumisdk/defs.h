#pragma once
#include <stddef.h>
#include <string>
#include <cstdint>
#include <type_traits>
#include "id.h"
#include "platform.h"
#include "optiondefs.h"

typedef std::uintptr_t APPSID;
typedef size_t RSCID;
typedef uint32_t HASHID;
typedef uint32_t UNIQUEID;
typedef std::type_index TYPEID;

//#define appId(ptr) reinterpret_cast<std::uintptr_t>(&ptr)
#define appId(ptr) reinterpret_cast<std::uintptr_t>(ptr)
#define rscdId(name) std::hash<std::string>{}(std::string(name))
#define hashId(name) FNV1A(name)

#define extend public virtual

