# TagFS Core Library

A thread-safe, cross-platform tag-based file system core implementation in C.

## Features
- Tag-based file system operations
- Read-only interface with extensible design for write operations
- Thread-safe implementation
- Cross-platform support (Linux, Windows, macOS, Android, iOS)
- Unicode support (UTF-8 and UTF-16)

## Requirements
- C17 compatible compiler
- CMake 3.15+
- GoogleTest (for testing, automatically downloaded)

## Building

### Quick Start
```bash
# Create and enter build directory
mkdir -p build
cd build

# Configure (with tests enabled)
cmake .. -DBUILD_TESTS=ON

# Build
cmake --build . --config Release

# Run tests
ctest --build-config Release --output-on-failure

# Create packages
cmake --build . --target package
```

### Build Options
- `-DBUILD_TESTS=ON|OFF` - Enable/disable building tests (default: OFF)
- `-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo` - Set build type

### Output Locations
- **Linux/MacOS**:
  - Library: `build/libtagfs-core.a`
  - Example: `build/tagfs-hello`
  - Tests: `build/tests/unit/tagfs_tests`
  - Package: `build/tagfs-<version>.tar.gz`

- **Windows**:
  - Library: `build/Release/tagfs-core.lib`
  - Example: `build/Release/tagfs-hello.exe`
  - Tests: `build/tests/unit/Release/tagfs_tests.exe`
  - Package: `build/tagfs-<version>.zip`

### Clean Build
```bash
# Linux/MacOS
rm -rf build/*

# Windows
rd /s /q build
mkdir build
```

## Integration
See [Integration Guide](docs/integration.md) for details on using this library as a git submodule.

## Version
0.1.6 - Initial Release (Read-Only Implementation)

## License
MIT License
