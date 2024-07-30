

add_library(DUMICORE STATIC)

target_include_directories(DUMICORE PRIVATE ${DUMICOMMON_DIR})
target_link_libraries(DUMICORE PRIVATE DUMICOMMON)

target_sources(
    DUMICORE
PUBLIC

PRIVATE
    appman.cpp
INTERFACE
)

message("Includes...")
get_property(dirs DIRECTORY ${DUMICORE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()
message("Includes Done")
