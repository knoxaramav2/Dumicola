message(">> dumisdk @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(dumisdk SHARED)

#Version config
set(DUMICOMM_MAJOR 0)
set(DUMICOMM_MINOR 0)
set(DUMICOMM_BUILD 1)
message("CONFIG VERSION.h.in")
configure_file(dumisdk_version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk_version.hpp)

message("INCLUDE ${CMAKE_BINARY_DIR}/dumisdk")
target_include_directories(dumisdk PRIVATE "${CMAKE_BINARY_DIR}/dumisdk")

target_sources(
    dumisdk
PUBLIC 
    dumisdk.cpp
    utils.cpp
    dtypes.cpp
PRIVATE

)

#Values

