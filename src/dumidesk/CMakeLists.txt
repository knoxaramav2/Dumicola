message(">> DUMIDESK @ ${DUMIDESK_DIR}")

add_executable(dumidesk)

target_sources(
    dumidesk
PRIVATE
    dumidesk.cpp
)

target_include_directories(dumidesk 
PRIVATE 
    ${DUMILOGGER_DIR}
    ${DUMISDK_DIR}
    ${DUMICORE_DIR}
    )
target_link_libraries(dumidesk PRIVATE dumilogger dumicore dumisdk)