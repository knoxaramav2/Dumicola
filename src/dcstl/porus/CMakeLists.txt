message(">> PORUS @ ${SDL_PORUS_DIR}")

add_library(porus)
set_target_properties(porus PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(porus
PUBLIC
    ${DUMISDK_DIR}
    ${DCUTILS_DIR}
)

target_sources(porus
PUBLIC
    porus.cpp
)
