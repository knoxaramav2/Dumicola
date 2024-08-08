message(">> DUMICORE @ ${DUMICORE_DIR}")

add_library(dumicore SHARED)

target_include_directories(
    dumicore 
PUBLIC 
    ${DUMISDK_DIR} 
    ${DUMILOGGER_DIR}
    ${DATAMAN_DIR} 
    ${SERVICEMAN_DIR} 
    ${APPRUNNER_DIR}
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

PRIVATE
    dumicore.cpp
INTERFACE
)
