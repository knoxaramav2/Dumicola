message(">> TESTS @ ${CMAKE_CURRENT_SOURCE_DIR}")
enable_testing()

add_executable(test_sdk dtypes_test.cpp)
target_include_directories(test_sdk PRIVATE ${DUMISDK_DIR})
target_link_libraries(test_sdk PRIVATE DUMISDK)
add_test(NAME TestSdk COMMAND test_sdk)

