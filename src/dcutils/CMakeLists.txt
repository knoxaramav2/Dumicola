message(">> utils @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dcutils STATIC)
set_target_properties(dcutils PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(dcutils PUBLIC ${DCUTILS_DIR})

target_sources(dcutils
PUBLIC
    dc_string.hpp
)