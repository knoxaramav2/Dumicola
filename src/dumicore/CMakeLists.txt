message(">> DUMICORE @ ${DUMICORE_DIR}")

add_library(DUMICORE STATIC)

target_include_directories(DUMICORE PRIVATE ${DUMISDK_DIR})
target_link_libraries(DUMICORE PRIVATE DUMISDK)

message("LINK TO ${DUMISDK_DIR}")

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
