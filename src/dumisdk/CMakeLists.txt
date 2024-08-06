message(">> dumisdk @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(dumisdk STATIC)

configure_file(dumisdk_version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk_version.hpp)

message("SDK : UTILS << ${DCUTILS_DIR}")

target_include_directories(dumisdk PRIVATE ${DCUTILS_DIR})
target_link_libraries(dumisdk PUBLIC dcutils)

target_sources(
    dumisdk
PUBLIC 
    dumisdk.cpp
    dtypes.cpp
PRIVATE

)

#Values

