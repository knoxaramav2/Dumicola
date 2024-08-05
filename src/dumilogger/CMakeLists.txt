message(">> dumilogger @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumilogger SHARED)

target_sources(dumilogger
PRIVATE
    dumiLogger.cpp
)


