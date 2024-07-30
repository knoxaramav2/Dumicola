message(">> DUMICOMMON @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(DUMICOMMON SHARED)

#Version config
set(DUMICOMM_MAJOR 0)
set(DUMICOMM_MINOR 0)
set(DUMICOMM_BUILD 1)
message("CONFIG VERSION.h.in")
configure_file(dumicommon_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/dumicommon_version.h)

message("INCLUDE ${CMAKE_BINARY_DIR}/dumicommon")
target_include_directories(DUMICOMMON PRIVATE "${CMAKE_BINARY_DIR}/dumicommon")

target_sources(
    DUMICOMMON
PUBLIC 
    dumicommon.cpp
    dtypes.cpp
PRIVATE

)

#Values

