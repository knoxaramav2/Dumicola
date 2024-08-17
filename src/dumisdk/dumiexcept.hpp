#pragma once

#include <stdexcept>
#include <cstring>

namespace dumisdk{
    class dumiexception: public std::runtime_error{
    public:

        explicit dumiexception();
        explicit dumiexception(char*message);
        explicit dumiexception(const char*message);
        ~dumiexception() = default;
    }; 
}




