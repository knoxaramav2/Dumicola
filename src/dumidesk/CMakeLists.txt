

add_executable(DUMIDESK)
#link_libraries(DUMIDESK PRIVATE DUMICOMMON)

target_sources(
    DUMIDESK
PRIVATE
    dumidesk.cpp
)

target_include_directories(DUMIDESK 
PRIVATE 
    "${CMAKE_BINARY_DIR}/DUMICOMMON"
    "${CMAKE_BINARY_DIR}/DUMICORE"
    )
target_link_libraries(DUMIDESK PRIVATE DUMICOMMON)