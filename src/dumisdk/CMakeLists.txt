message(">> DUMISDK @ ${CMAKE_CURRENT_SOURCE_DIR}")

#Setup library
add_library(dumisdk STATIC)

target_include_directories(dumisdk 
PRIVATE 
    ${DCUTILS_DIR} 
PUBLIC
    ${CONFIG_DIR}
)

configure_file(dumisdk_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk_version.h)

target_link_libraries(dumisdk PUBLIC dcutils)

target_sources(
    dumisdk
PUBLIC 
    dumisdk.cpp
    dtypes.cpp
    dumiexcept.cpp
    service_interfaces.cpp
    component.cpp
PRIVATE

)

#Values

