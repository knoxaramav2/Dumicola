message(">> DUMIENGINE @ ${CMAKE_CURRENT_SOURCE_DIR}")

if(DEFINED _WINDOWS)
    add_library(dumiengine STATIC)
else()
    add_library(dumiengine SHARED)
endif()

target_link_libraries(dumiengine PUBLIC dcutils dataman)
target_include_directories(dumiengine
PRIVATE 
    ${DCUTILS_DIR} 
    ${DATAMAN_DIR}
PUBLIC
    ${CONFIG_DIR}
)

target_sources(
    dumiengine
PRIVATE
    dlEngine.cpp
)