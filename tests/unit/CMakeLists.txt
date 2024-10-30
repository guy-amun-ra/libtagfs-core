enable_testing()

add_executable(tagfs_tests
    main_test.cpp
)

target_link_libraries(tagfs_tests
    PRIVATE
    tagfs
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME tagfs_unit_tests COMMAND tagfs_tests)
