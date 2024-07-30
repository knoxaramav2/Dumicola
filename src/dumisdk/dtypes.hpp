#pragma once

#include "defs.hpp"

#include <string>

namespace dumisdk
{
    enum DumiType{
        NONE,
        BOOL,
        INTEGER, DECIMAL,
        STRING,
        LOOKUP, LIST,
        BLOB
    };

    template<typename T>
    struct DType{
        APPSID id;
        DumiType type;
        T* value;

        DType(DumiType type);
        ~DType();
    };
    
    struct TypeRef{
        APPSID id;
        DType<void>* typeData;

        TypeRef(DType<void> typeData);
    };
}
