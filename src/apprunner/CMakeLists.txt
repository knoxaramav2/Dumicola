message(">> SERVICEMANAGER @ ${DUMICORE_DIR}")

add_library(apprunner STATIC)

target_include_directories(apprunner PRIVATE ${DUMISDK_DIR})
target_link_libraries(apprunner PRIVATE dumisdk)

target_sources(
    apprunner
PUBLIC
    
)