#pragma once

#include <string>
#include <cstdint>
#include <typeindex>

uint32_t nextId();
uint32_t FNV1A(std::string raw);

#define addrId(obj) reinterpret_cast<APPSID>(&obj);
#define NAMEOF(x) #x

#define idFromTU(T, U) std::is_void<T>::value ? \
    std::type_index(typeid(U)) : std::type_index(typeid(T))
#define typeId(T) std::type_index(typeid(T))
#define idPairTU(T, U) std::make_pair(typeId(T),typeId(U))
#define TFactory(T) []() -> std::unique_ptr<void>{ return std::make_unique<U>(); }

typedef std::type_index TypeId;
