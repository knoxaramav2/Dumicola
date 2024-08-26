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

if(NOT DEFINED AUX_AS)
    set(AUX_BUILD SHARED)
else()
    set(AUX_BUILD AUX_AS)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cpp.hint ${CMAKE_BINARY_DIR}/cpp.hint COPYONLY)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Set the output directories for different types of targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)

set(ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

message("Build Version: ${MAJOR_VRS}.${MINOR_VRS}.${BUILD_VRS}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)

set(DCUTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dcutils)
set(DUMISDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk)
set(DUMILANG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumilang)
set(DUMISDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dcstl)
set(LIBMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libmanager)
set(DATAMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/datamanager)
set(DUMIENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumiengine)
set(SERVICEMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/servicemanager)
set(APPRUNNER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/apprunner)
set(DUMICORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumicore)
set(DUMIDESK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumidesk)
set(DUMIMOBILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dumimobile/app/src/main/cpp)

add_subdirectory(config)
add_subdirectory(dcutils)
add_subdirectory(dumisdk)
add_subdirectory(dumilang)
add_subdirectory(dcstl)
add_subdirectory(libmanager)
add_subdirectory(datamanager)
add_subdirectory(dumiengine)
add_subdirectory(servicemanager)
add_subdirectory(apprunner)
add_subdirectory(dumicore)
add_subdirectory(dumidesk)
add_subdirectory(Dumimobile/app/src/main/cpp)

#Testing
enable_testing()
add_subdirectory(test)

