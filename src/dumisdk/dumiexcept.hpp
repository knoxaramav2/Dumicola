#pragma once

#include <exception>
#include <cstring>

class dumiexception: public std::exception{
    const char* msg;
    public:

    dumiexception(): msg("Dumi runtime exception"){}
    dumiexception(char*message): msg(message){}
    dumiexception(const char*message): msg(message){}

    const char* what(){ return msg; }
};

