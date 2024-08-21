message(">> PORUS @ ${SDL_PORUS_DIR}")

add_library(porus SHARED)
set_target_properties(porus PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(porus
PUBLIC
    ${DUMISDK_DIR}
    ${DCUTILS_DIR}
)

target_link_libraries(porus PUBLIC dumisdk PRIVATE dcutils)

target_sources(porus
PUBLIC
    porus.cpp
)
