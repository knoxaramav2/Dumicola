message(">> DUMILANG @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumilang STATIC)

target_link_libraries(dumilang PUBLIC dcutils dataman)
target_include_directories(dumilang
PRIVATE 
    ${DCUTILS_DIR} 
    ${DATAMAN_DIR}
PUBLIC
    ${CONFIG_DIR}
)

configure_file(dumilang.h.in ${CMAKE_CURRENT_SOURCE_DIR}/dumilang.h)

target_sources(
    dumilang
PRIVATE
    token.cpp
    tokenizer.cpp
)