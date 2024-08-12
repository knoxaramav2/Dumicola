message(">> DUMISDK @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(dumisdk STATIC)

message("!!DUMISDK INCLUDE ${CONFIG_DIR}")

target_include_directories(dumisdk 
PRIVATE 
    ${DCUTILS_DIR} 
PUBLIC
    ${CONFIG_DIR}
)

configure_file(dumisdk_version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk_version.hpp)

target_link_libraries(dumisdk PUBLIC dcutils)

target_sources(
    dumisdk
PUBLIC 
    dumisdk.cpp
    dtypes.cpp
    service_interfaces.cpp
    component.cpp
PRIVATE

)

#Values

