# Ensure Google Test is available
if(NOT TARGET GTest::gtest_main)
    message(FATAL_ERROR "Google Test is not available. Make sure BUILD_TESTS is ON.")
endif()

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
include(GoogleTest)
gtest_discover_tests(tagfs_tests)

# Add custom target for running tests
add_custom_target(run_tests
    COMMAND tagfs_tests
    DEPENDS tagfs_tests
)

# Optional: Set properties for CTest
set_tests_properties(${ALL_TESTS} PROPERTIES
    TIMEOUT 10  # Set a timeout for each test (adjust as needed)
)

# Optional: Add test to default build target
add_dependencies(tagfs-core tagfs_tests)