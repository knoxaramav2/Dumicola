#include "dtypes.hpp"
#include "utils.hpp"

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <vector>
#include <map>
#include <format>

dumisdk::DCMemObj::DCMemObj(DumiBaseType t_base, DumiExtType t_ext)
{
    this->id = addrId(*this);
    this->type = SET_DTYPE_EXT(t_base, t_ext);
}

template <typename T>
inline dumisdk::DCType<T>::DCType(DumiBaseType t_base, DumiExtType t_ext, T initialValue)
    :DCMemObj(t_base, t_ext)
{
    this->__value = new T(initialValue);
}

template <typename T>
dumisdk::DCType<T>::~DCType()
{
    delete __value;
}

template<typename T>
T dumisdk::DCType<T>::get()
{
    return *__value;
}

template<typename T>
int dumisdk::DCType<T>::set(T value)
{
    *__value = value;
    return 0;
}

/** 
 * Type definitions 
 **/
dumisdk::DCBoolean::DCBoolean()
    :DCType<bool>(DumiBaseType::BOOL, DumiExtType::BASIC_DTYPE, false)
    {}

dumisdk::DCInteger::DCInteger()
    :DCType<int32_t>(DumiBaseType::INTEGER, DumiExtType::BASIC_DTYPE, 0)
    {}

dumisdk::DCDecimal::DCDecimal()
    :DCType<double>(DumiBaseType::DECIMAL, DumiExtType::BASIC_DTYPE, 0.0f)
    {}

dumisdk::DCString::DCString()
    :DCType<std::string>(DumiBaseType::STRING, DumiExtType::BASIC_DTYPE, "")
    {}

dumisdk::DCMap::DCMap()
    :DCType<std::map<APPSID, dumisdk::DCMemObj*>>(DumiBaseType::MAP, DumiExtType::BASIC_DTYPE, {})
    {}

dumisdk::DCMemObj *dumisdk::DCMap::operator[](APPSID id)
{
    return nullptr;
}

dumisdk::DCList::DCList()
    :DCType<std::vector<dumisdk::DCMemObj*>>(DumiBaseType::LIST, DumiExtType::BASIC_DTYPE, {})
    {}


