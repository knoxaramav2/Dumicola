message(">> dumisdk @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(DUMISDK SHARED)

#Version config
set(DUMICOMM_MAJOR 0)
set(DUMICOMM_MINOR 0)
set(DUMICOMM_BUILD 1)
message("CONFIG VERSION.h.in")
configure_file(dumisdk_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk_version.h)

message("INCLUDE ${CMAKE_BINARY_DIR}/dumisdk")
target_include_directories(DUMISDK PRIVATE "${CMAKE_BINARY_DIR}/dumisdk")

target_sources(
    DUMISDK
PUBLIC 
    dumisdk.cpp
    utils.cpp
    dtypes.cpp
    logger.cpp
    utils.cpp
PRIVATE

)

#Values

