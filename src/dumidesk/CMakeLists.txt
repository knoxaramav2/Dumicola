message(">> DUMIDESK @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(DUMIDESK)
#link_libraries(DUMIDESK PRIVATE dumisdk)

target_sources(
    DUMIDESK
PRIVATE
    dumidesk.cpp
)

target_include_directories(DUMIDESK 
PRIVATE 
    ${dumisdk_DIR}
    ${DUMICORE_DIR}
    )
target_link_libraries(DUMIDESK PRIVATE dumisdk)