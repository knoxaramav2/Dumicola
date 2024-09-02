message(">> DUMIENGINE @ ${CMAKE_CURRENT_SOURCE_DIR}")

if(DEFINED _WINDOWS)
    add_library(dumiengine STATIC)
else()
    add_library(dumiengine SHARED)

    if(DEFINED _LINUX)
        target_link_libraries(dumiengine PRIVATE pthread)
    endif()
endif()

target_link_libraries(dumiengine PUBLIC dcutils dataman libman dumisdk)
target_include_directories(dumiengine
PRIVATE 
    ${DCUTILS_DIR} 
    ${DATAMAN_DIR}
    ${LIBMAN_DIR}
    ${DUMISDK_DIR}
PUBLIC
    ${CONFIG_DIR}
)

target_sources(
    dumiengine
PRIVATE
    dlEngine.cpp
    alu.cpp
    programblock.cpp
)