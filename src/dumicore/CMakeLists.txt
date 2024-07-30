

add_library(DUMICORE STATIC)

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)

target_include_directories(DUMICORE PRIVATE "${CMAKE_BINARY_DIR}/DUMICOMMON")
target_link_libraries(DUMICORE PRIVATE DUMICOMMON)