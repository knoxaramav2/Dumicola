message(">> DATAMANAGER @ ${DUMICORE_DIR}")

add_library(dataman STATIC)

target_include_directories(dataman PRIVATE ${DUMISDK_DIR})
target_link_libraries(dataman PRIVATE dcutils dumisdk)

target_sources(
    dataman
PUBLIC
    dataman.cpp
)