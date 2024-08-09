message(">> DUMICORE @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumicore SHARED)

target_include_directories(
    dumicore 
PUBLIC 
    ${DUMISDK_DIR} 
    ${DUMILOGGER_DIR}
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
    dumilogger
    serviceman 
    dataman 
    apprunner)

target_sources(
    dumicore
PUBLIC
    #dumicore.hpp
PRIVATE
    dumicore.cpp
INTERFACE
)
