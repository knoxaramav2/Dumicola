message(">> DUMI SDL PROJECT GROUP")

set(SDL_VULKAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vulkan)
set(SDL_HYPATIA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hypatia)
set(SDL_PORUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/porus)

add_subdirectory(vulkan)
add_subdirectory(hypatia)
add_subdirectory(porus)

# set_output_directories(vulkan)
# set_output_directories(hypatia)
# set_output_directories(porus)

# set_target_properties(
#     vulkan hypatia porus
#     PROPERTIES
#     CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_}/stl)

message("STL LIBS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")