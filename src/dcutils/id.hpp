#pragma once

#include <string>
#include <cstdint>

uint32_t nextId();
uint32_t FNV1A(std::string raw);

#define addrId(obj) reinterpret_cast<APPSID>(&obj);
#define NAMEOF(x) #x
