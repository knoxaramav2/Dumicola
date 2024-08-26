message(">> DUMICORE @ ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(dumicore STATIC)

target_include_directories(
    dumicore 
PUBLIC 
    ${DCUTILS_DIR}
    ${DUMISDK_DIR} 
    ${SERVICEMAN_DIR} 
    ${APPRUNNER_DIR}
    ${DUMICORE_DIR}
PRIVATE
    ${DUMIENGINE_DIR}
    ${DUMILANG_DIR}
    )
    
target_link_libraries(
    dumicore 
PRIVATE 
    dcutils 
    dumilang 
    apprunner
PUBLIC
    serviceman
    dumisdk
    dumiengine
    )

target_sources(
    dumicore
PUBLIC
    #dumicore.h
PRIVATE
    dumicore.cpp
INTERFACE
)
