message(">> CONFIG @ ${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(_ANDROID "" PARENT_SCOPE)
    if(CMAKE_ANDROID_ARCH_ABI MATCHES "armeabi-v7a|x86")
        set(_ANDROID32)
    elseif(CMAKE_ANDROID_ARCH_ABI MATCHES "arm64-v8a|x86_64")
        set(_ANDROID64)
    else()
        message(WARNING "Unknown or unsupported architecture: ${CMAKE_ANDROID_ARCH_ABI}")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
else()
    message( FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

configure_file(platform.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/platform.hpp)

message("OPT_PERF >> ${OPT_PERF}")
if(DEFINED OPT_PERF)
    set(OINLINE inline)
elseif()
    set(ONLINE TEST)
endif()

configure_file(optimize.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/optimize.hpp @ONLY)




