include(GoogleTest)

set(TEST_FILES
    Test_Service3E.cpp
    Test_Service22.cpp
)

add_executable(
    UNIT_TEST
    ${TEST_FILES}
)
target_link_libraries(
    UNIT_TEST
    GTest::gtest_main
    GTest::gmock_main
    UdsCfgLib
    UdsLib
)

gtest_discover_tests(UNIT_TEST)
