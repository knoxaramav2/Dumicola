message(">> DUMIDESK @ ${DUMIDESK_DIR}")

add_executable(dumidesk)

target_sources(
    dumidesk
PRIVATE
    dumidesk.cpp
    logger.cpp
)

target_include_directories(dumidesk 
PRIVATE 
    ${DUMISDK_DIR}
    ${DUMICORE_DIR}
    )
target_link_libraries(dumidesk PRIVATE dumicore dumisdk)