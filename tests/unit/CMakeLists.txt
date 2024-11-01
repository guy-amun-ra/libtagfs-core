# tests/unit/CMakeLists.txt

# Create the test executable
add_executable(tagfs_tests
    main_test.cpp
)

# Link against the library and Google Test
target_link_libraries(tagfs_tests
    PRIVATE
    tagfs-core
    GTest::gtest
    GTest::gtest_main
)

# Add include directories
target_include_directories(tagfs_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)

# Discover and add tests
gtest_discover_tests(tagfs_tests)

# Optional: Set properties for CTest
set_tests_properties(${ALL_TESTS} PROPERTIES
    TIMEOUT 10  # Set a timeout for each test (adjust as needed)
)