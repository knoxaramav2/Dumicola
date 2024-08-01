message(">> DUMIDESK @ ${DUMIDESK_DIR}")

add_executable(DUMIDESK)

target_sources(
    DUMIDESK
PRIVATE
    dumidesk.cpp
)

target_include_directories(DUMIDESK 
PRIVATE 
    ${DUMISDK_DIR}
    ${DUMICORE_DIR}
    )
target_link_libraries(DUMIDESK PRIVATE DUMISDK)