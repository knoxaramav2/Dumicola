#include "dtypes.hpp"

#include <type_traits>
#include <exception>
#include <concepts>
#include <vector>
#include <map>

template <typename T>
dumisdk::DType<T>::DType(DumiType type)
{
    this->type = type;

    switch(type){
        case DumiType::NONE: this->value = nullptr; break;
        case DumiType::BOOL: this->value = new bool; break;
        case DumiType::INTEGER: this->value = new long; break;
        case DumiType::DECIMAL: this->value = new double; break;
        case DumiType::STRING: this->value = new std::string; break;
        case DumiType::LOOKUP: this->value = new std::map<APPSID, TypeRef>; break;
        case DumiType::LIST: this->value = new std::vector<T>; break;
    }

    this->id = appId(this->value);
}

template <typename T>
dumisdk::DType<T>::~DType()
{
    if(this->value != nullptr){ delete this->value; }
}