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
    COMMAND ${GIT_EXECUTABLE} describe --tags --dirty
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

# If Git is not available or no tag is found, use a default version
if("${PROJECT_VERSION}" STREQUAL "")
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