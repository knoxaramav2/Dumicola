message(">> VULKAN @ ${SDL_VULKAN_DIR}")

add_library(vulkan SHARED)
set_target_properties(vulkan PROPERTIES LINKER_LANGUAGE CXX
    #WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_include_directories(vulkan
PUBLIC
    ${DUMISDK_DIR}
    ${DCUTILS_DIR}
    ${CONFIG_DIR}
)

target_link_libraries(vulkan PUBLIC dumisdk PRIVATE dcutils)
target_compile_definitions(vulkan PRIVATE VULKAN_EXPORT)

target_sources(vulkan
PUBLIC
    vulkan.cpp
)
