message(">> TESTS @ ${CMAKE_CURRENT_SOURCE_DIR}")
#enable_testing()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

add_library(kassert kassert.cpp)

add_executable(test_sdk dumi_tests.cpp dtypes_test.cpp)
target_include_directories(test_sdk PRIVATE ${DUMISDK_DIR})
target_link_libraries(test_sdk PRIVATE DUMISDK kassert)

add_test(NAME TestSdk COMMAND test_sdk)

