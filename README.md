# JacLib

![Linux tests](https://github.com/Moztanku/JacLib/actions/workflows/tests_linux.yaml/badge.svg?branch=main)
![Windows tests](https://github.com/Moztanku/JacLib/actions/workflows/tests_windows.yaml/badge.svg?branch=main)

![License](https://img.shields.io/github/license/Moztanku/JacLib)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)

***My utility library for C++20 made for personal use and learning purposes.***

## Features
- **Multiple-platform support**: Both Windows and Linux are supported
- **Static/Dynamic compilation**: The library can be compiled as a static or dynamic library
- **Documentation**: Every module is documented with Doxygen style comments

## Modules
- **print.hpp**: A print function with multiple overloads that supports various log levels, (<span style="color:orange">"*{} {}*"</span>, {<span style="color:orange">"*formatted*"</span>, <span style="color:orange">"*strings*"</span>}), colored <span style="color:yellow">[HEADERS]</span> and source location <span style="color:grey">@ README.md:16</span>
- **types.hpp**: A set of type aliases
- **debug.hpp**: A constexpr constant that is enabled when the compiler is in debug mode

## How to include in your project
***You can see example usage in `tst\CMakeLists.txt`***

### Requirements
- **CMake**
- **C++20**

### Steps
1. **Clone the repository**
```bash
git clone https://github.com/Moztanku/JacLib.git path/to/JacLib
```
2. **Include the library in your CMake project**
```cmake
add_subdirectory(path/to/JacLib)
target_link_libraries(your_target PRIVATE JacLib)
```
3. **Include the library in your source files**
```cpp
#include "jac/print.hpp"

int main() {
    jac::print("{} {}!", {"Hello", "World"});

    return 0;
}
```

## How to build tests

### Requirements
- **CMake**
- **C++20**
- **Gtest**

### Steps
1. **Clone the repository**
```bash
git clone https://github.com/Moztanku/JacLib.git path/to/JacLib
```
2. **Build the project and tests**
```bash
# Enter the repository directory
cd path/to/JacLib
# Configure step
cmake -B build -S . -DJacLib_BUILD_TESTS=ON
# Build step
cmake --build build
```
3. **Run the tests**
```bash
# Linux
./build/tst/JacLib_tests

# Windows
./build/tst/{Debug|Release}/JacLib_tests.exe
```

## Build options
- **JacLib_BUILD_TESTS={ON|OFF}**: Build the tests (default: ***OFF***)
- **BUILD_SHARED_LIBS={ON|OFF}**: Build the library as a shared library (default: ***ON***)
- **CMAKE_BUILD_TYPE={Release|Debug}**: Build type on **Linux** (default: ***Release***)
- **--config {Release|Debug}**: Build type, set during build step on **Windows** (default: ***Release***)
