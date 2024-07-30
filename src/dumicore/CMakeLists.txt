

add_library(DUMICORE STATIC)

target_include_directories(DUMICORE PRIVATE ${DUMICOMMON_DIR})
target_link_libraries(DUMICORE PRIVATE DUMICOMMON)

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
