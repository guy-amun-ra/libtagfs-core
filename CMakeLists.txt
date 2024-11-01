cmake_minimum_required(VERSION 3.10)

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

project(libtagfs-core VERSION ${PROJECT_VERSION}
        DESCRIPTION "A thread-safe, cross-platform tag-based file system core implementation"
        LANGUAGES C CXX)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
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
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Enable testing
    enable_testing()
    include(GoogleTest)
    
    add_subdirectory(tests/unit)
endif()

# Installation rules
include(GNUInstallDirs)
install(TARGETS tagfs-core tagfs-hello
    EXPORT tagfs-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/tagfs
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/version.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tagfs
)

# Export targets
install(EXPORT tagfs-targets
    FILE tagfs-targets.cmake
    NAMESPACE tagfs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tagfs
)

# Generate and install package configuration
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tagfs-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/tagfs-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tagfs
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/tagfs-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/tagfs-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/tagfs-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tagfs
)

# Packaging
set(CPACK_PACKAGE_NAME "tagfs")
set(CPACK_PACKAGE_VENDOR "TagFS")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TagFS Core Library - A tag-based file system implementation")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "tagfs")

# Make LICENSE and README optional
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
endif()

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)