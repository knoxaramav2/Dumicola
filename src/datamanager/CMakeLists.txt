message(">> DATAMANAGER @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dataman STATIC)

target_include_directories(
dataman 
    PRIVATE 
${DCUTILS_DIR} 
    PUBLIC
${DUMISDK_DIR}
${CONFIG_DIR} 
)

target_link_libraries(dataman PRIVATE dcutils dumisdk)
set_target_properties(dataman PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_sources(
    dataman
PUBLIC
    dataman.cpp
)