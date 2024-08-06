message(">> SERVICEMANAGER @ ${DUMICORE_DIR}")

add_library(serviceman STATIC)

target_include_directories(serviceman PRIVATE ${DUMISDK_DIR})
target_link_libraries(serviceman PRIVATE dumisdk)

target_sources(
    serviceman
PUBLIC
    serviceman.cpp
)