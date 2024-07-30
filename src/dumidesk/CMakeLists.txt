message(">> DUMIDESK @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(DUMIDESK)
#link_libraries(DUMIDESK PRIVATE DUMICOMMON)

target_sources(
    DUMIDESK
PRIVATE
    dumidesk.cpp
)

target_include_directories(DUMIDESK 
PRIVATE 
    ${DUMICOMMON_DIR}
    ${DUMICORE_DIR}
    )
target_link_libraries(DUMIDESK PRIVATE DUMICOMMON)