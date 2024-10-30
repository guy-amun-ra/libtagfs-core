enable_testing()

add_executable(tagfs_tests
    main_test.cpp
)

target_link_libraries(tagfs_tests
    PRIVATE
    tagfs-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(tagfs_tests)