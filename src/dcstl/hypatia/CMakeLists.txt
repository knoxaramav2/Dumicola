message(">> HYPATIA @ ${SDL_HYPATIA_DIR}")

add_library(hypatia SHARED)
set_target_properties(hypatia PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(hypatia
PUBLIC
    ${DUMISDK_DIR}
    ${DCUTILS_DIR}
)

target_link_libraries(hypatia PUBLIC dumisdk PRIVATE dcutils)

target_sources(hypatia
PUBLIC
    hypatia.cpp
)
