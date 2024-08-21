message(">> LIBRARY MANAGER @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(libman STATIC)

target_include_directories(libman PRIVATE ${DUMISDK_DIR})
target_link_libraries(libman PRIVATE dumisdk)

target_sources(
    libman
PUBLIC
    libManager.cpp
)
