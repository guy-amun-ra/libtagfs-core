cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()
include(GoogleTest)

# Get version from Git
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # Remove 'v' prefix if present
  string(REGEX REPLACE "^v" "" PROJECT_VERSION "${GIT_TAG}")
endif()
# If Git tag not found, use VERSION file
if("${PROJECT_VERSION}" STREQUAL "")
  file(STRINGS "VERSION" PROJECT_VERSION)
endif()

# Validate version format
if(NOT PROJECT_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
  message(STATUS "Invalid version format: ${PROJECT_VERSION}, using VERSION file")
  file(STRINGS "VERSION" PROJECT_VERSION)
endif()

project(libtagfs-core VERSION ${PROJECT_VERSION})

# Configure version header
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/version.h
    @ONLY
)

# Main library
add_library(tagfs-core STATIC
    src/core.c
)

target_include_directories(tagfs-core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_compile_definitions(tagfs-core PUBLIC TAGFS_VERSION="${PROJECT_VERSION}")

# Example executable
add_executable(tagfs-hello
    examples/hello.c
)

target_link_libraries(tagfs-hello
    PRIVATE
    tagfs-core
)

# Tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests/unit)
endif()