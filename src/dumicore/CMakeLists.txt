message(">> DUMICORE @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(DUMICORE STATIC)

target_include_directories(DUMICORE PRIVATE ${DUMICOMMON_DIR})
target_link_libraries(DUMICORE PRIVATE DUMICOMMON)


message("LINK TO ${DUMICOMMON_DIR}")

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
