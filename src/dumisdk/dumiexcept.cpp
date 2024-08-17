#include "dumiexcept.hpp"

dumisdk::dumiexception::dumiexception():std::runtime_error("Dumi runtime exception"){}
dumisdk::dumiexception::dumiexception(char*message):std::runtime_error(message){}
dumisdk::dumiexception::dumiexception(const char*message):std::runtime_error(message){}

