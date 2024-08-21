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

#if(MSVC)
#    add_compile_options("/MDd /ZI /Ob0 /Od /RTC1")
#    add_link_options("/debug /INCREMENTAL /LTCG:OFF")
#endif()

#add_compile_definitions("-g3")

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
set(DUMISDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dcstl)
set(LIBMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libmanager)
set(DATAMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/datamanager)
set(SERVICEMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/servicemanager)
set(APPRUNNER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/apprunner)
set(DUMICORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumicore)
set(DUMIDESK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumidesk)
set(DUMIMOBILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android/app/src/main/cpp)

add_subdirectory(config)
add_subdirectory(dcutils)
add_subdirectory(dcstl)
add_subdirectory(dumisdk)
add_subdirectory(libmanager)
add_subdirectory(datamanager)
add_subdirectory(servicemanager)
add_subdirectory(apprunner)
add_subdirectory(dumicore)
add_subdirectory(dumidesk)
add_subdirectory(android/app/src/main/cpp)

#Testing
enable_testing()
#set(DUMITEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumitest)
add_subdirectory(test)

