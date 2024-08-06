message(">> DUMICORE @ ${DUMICORE_DIR}")

add_library(dumicore SHARED)

target_include_directories(dumicore PRIVATE ${DUMISDK_DIR} ${DATAMAN_DIR} ${SERVICEMAN_DIR} ${APPRUNNER_DIR})
target_link_libraries(dumicore PRIVATE dcutils dumisdk dataman apprunner)

target_sources(
    dumicore
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)
