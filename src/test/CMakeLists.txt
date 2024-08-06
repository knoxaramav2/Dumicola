message(">> TESTS @ ${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

add_library(kassert kassert.cpp)

add_executable(test_sdk_types dtypes_test.cpp)
target_include_directories(test_sdk_types PRIVATE ${DUMISDK_DIR} ${DATAMAN_DIR})
target_link_libraries(test_sdk_types PRIVATE kassert dcutils dataman )
add_test(NAME TestSdk COMMAND test_sdk_types)

add_executable(test_msc msc_test.cpp)
target_include_directories(test_msc PRIVATE ${DUMISDK_DIR} ${DCUTILS_DIR})
target_link_libraries(test_msc PRIVATE kassert dcutils dumisdk )
add_test(NAME TestMisc COMMAND test_msc)


