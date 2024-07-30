cmake_minimum_required(VERSION 3.28)
project(DUMICOLA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(dumisdk_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumisdk)
set(DUMICORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumicore)
set(DUMIDESK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dumidesk)

message(${CMAKE_BINARY_DIR})

add_subdirectory(dumisdk)
add_subdirectory(dumicore)
add_subdirectory(dumidesk)