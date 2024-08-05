cmake_minimum_required(VERSION 3.28)
project(DUMICOLA)

#Version config
if(NOT DEFINED MAJOR_VRS) 
    set(MAJOR_VRS 0) 
endif()
if(NOT DEFINED MINOR_VRS) 
    set(MINOR_VRS 0) 
endif()
if(NOT DEFINED BUILD_VRS) 
    set(BUILD_VRS 0) 
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(DCUTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dcutils)
set(DUMILOGGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumilogger)
set(DUMISDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk)
set(DUMICORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumicore)
set(DUMIDESK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumidesk)

message(${CMAKE_BINARY_DIR})

add_subdirectory(dcutils)
add_subdirectory(dumilogger)
add_subdirectory(dumisdk)
add_subdirectory(dumicore)
add_subdirectory(dumidesk)

#Testing
enable_testing()
set(DUMITEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumitest)
add_subdirectory(test)