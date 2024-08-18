message(">> DUMI SDL PROJECT GROUP")

set(SDL_VULKAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vulkan)
set(SDL_HYPATIA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hypatia)
set(SDL_PORUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/porus)

add_subdirectory(vulkan)
add_subdirectory(hypatia)
add_subdirectory(porus)