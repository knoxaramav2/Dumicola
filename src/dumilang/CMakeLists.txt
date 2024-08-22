message(">> DUMILANG @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumilang STATIC)

target_link_libraries(dumilang PUBLIC dcutils)
target_include_directories(dumilang
PRIVATE 
    ${DCUTILS_DIR} 
PUBLIC
    ${CONFIG_DIR}
)

target_sources(
    dumilang
PRIVATE
    token.cpp
)