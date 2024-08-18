message(">> DUMICORE @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumicore SHARED)

target_include_directories(
    dumicore 
PUBLIC 
    ${DCUTILS_DIR}
    ${DUMISDK_DIR} 
    ${DATAMAN_DIR} 
    ${SERVICEMAN_DIR} 
    ${APPRUNNER_DIR}
    ${DUMICORE_DIR}
    )
    
target_link_libraries(
    dumicore 
PRIVATE 
    dcutils 
    dumisdk 
    serviceman 
    dataman 
    apprunner)

target_sources(
    dumicore
PUBLIC
    #dumicore.h
PRIVATE
    dumicore.cpp
INTERFACE
)
