message(">> DUMICORE @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(DUMICORE STATIC)

target_include_directories(DUMICORE PRIVATE ${dumisdk_DIR})
target_link_libraries(DUMICORE PRIVATE dumisdk)


message("LINK TO ${dumisdk_DIR}")

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
