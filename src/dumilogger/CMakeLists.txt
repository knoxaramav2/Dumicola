message(">> dumilogger @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumilogger STATIC)
target_link_libraries(dumilogger PRIVATE dcutils)
target_include_directories(dumilogger PRIVATE ${DCUTILS_DIR})

target_sources(dumilogger
PRIVATE
    dumiLogger.cpp
)


