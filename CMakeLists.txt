cmake_minimum_required(VERSION 3.15)

# Read version from VERSION file
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION_CONTENT)
string(STRIP "${VERSION_CONTENT}" VERSION_CONTENT)

project(libtagfs-core VERSION ${VERSION_CONTENT} LANGUAGES C CXX)

# Library
add_library(tagfs-core src/core.c)
target_include_directories(tagfs-core PUBLIC include)

# Example executable
add_executable(tagfs-hello examples/hello.c)
target_link_libraries(tagfs-hello PRIVATE tagfs-core)
