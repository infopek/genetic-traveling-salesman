if(BUILD_TESTING)
    add_executable(Test src/sample_test.cpp)

    find_package(Core REQUIRED)

    target_link_libraries(
        Test
            PUBLIC
                Core::Core
            PRIVATE
                GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(Test)
endif()
