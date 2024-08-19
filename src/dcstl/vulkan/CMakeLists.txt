message(">> VULKAN @ ${SDL_VULKAN_DIR}")

add_library(vulkan)
set_target_properties(vulkan PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(vulkan
PUBLIC
    ${DUMISDK_DIR}
    ${DCUTILS_DIR}
    ${CONFIG_DIR}
)

target_sources(vulkan
PUBLIC
    vulkan.cpp
)
