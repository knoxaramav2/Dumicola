#include "id.h"

static uint32_t __id_cntr = 1;

uint32_t nextId(){ return __id_cntr++; }
uint32_t FNV1A(std::string raw){
    const uint32_t _offset = 2166136261;
    const uint32_t _prime = 16777619;

    uint32_t hash = _offset;
    for(unsigned char byte : raw){
        hash = (hash^byte)*_prime;
    }

    return hash;
}

