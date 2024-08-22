message(">> TESTS @ ${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

#Platform tests
if(DEFINED _ANDROID)

elseif(DEFINED _DESKTOP)
    add_library(kassert kassert.cpp)
    target_include_directories(kassert PUBLIC ${DCUTILS_DIR})
    target_link_libraries(kassert PUBLIC dcutils )

    add_executable(dumi_tests)
    target_include_directories(dumi_tests 
    PRIVATE 
        ${DUMISDK_DIR} ${DCUTILS_DIR} ${SERVICEMAN_DIR} ${LIBMAN_DIR}
        ${DATAMAN_DIR} ${DUMICORE_DIR} 
        ${SDL_VULKAN_DIR} ${SDL_HYPATIA_DIR} ${SDL_PORUS_DIR}
        ${DUMILANG_DIR}
        )
    target_link_libraries(dumi_tests 
    PRIVATE 
        kassert dcutils dumisdk serviceman dataman dumicore libman dumilang
    )
    add_test(NAME TestGroup COMMAND dumi_tests)
    add_compile_definitions(DUMILANG_SRC="${DUMILANG_DIR}/src")

    target_sources(dumi_tests
    PRIVATE
        dumicore_testgroup.cpp
        msc_test.cpp
        service_tests.cpp
        component_test.cpp
        dtypes_test.cpp
        fixtures.cpp
        plugin_test.cpp
        dumilang_test.cpp
    )

endif()


