message(">> DUMICORE @ ${DUMICORE_DIR}")

add_library(dumicore STATIC)

target_include_directories(dumicore PRIVATE ${DUMISDK_DIR})
target_link_libraries(dumicore PRIVATE dumisdk)

message("LINK TO ${DUMISDK_DIR}")

target_sources(
    dumicore
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
