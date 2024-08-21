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
    set(_LINUX "" PARENT_SCOPE)
    set(_DESKTOP "" PARENT_SCOPE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(_WINDOWS "" PARENT_SCOPE)
    set(_DESKTOP "" PARENT_SCOPE)
else()
    message( FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

#add_compile_definitions(BUILD_CONFIG ${CMAKE_BUILD_TYPE})
set(BUILD_CONFIG ${CMAKE_BUILD_TYPE})
configure_file(environment.h.in ${CMAKE_CURRENT_SOURCE_DIR}/environment.h)

message("OPT_PERF >> ${OPT_PERF}")
if(DEFINED OPT_PERF)
    set(OINLINE inline)
elseif()
    set(ONLINE TEST)
endif()

configure_file(optimize.h.in ${CMAKE_CURRENT_SOURCE_DIR}/optimize.h @ONLY)
#configure_file(filedef.h.in ${CMAKE_CURRENT_SOURCE_DIR}/filedef.h)



