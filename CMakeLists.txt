cmake_minimum_required(VERSION 3.29)

project(JacLib)

## Options
option(${PROJECT_NAME}_BUILD_TESTS "Build tests" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(CMAKE_BUILD_TYPE "Build type" Release)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Set compiler flags based on compiler and build type
set(compiler_flags "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(compiler_flags "-g" "-O0" "-Wall" "-Wextra" "-Wpedantic" "-Werror" "-DDEBUG")
    else()
        set(compiler_flags "-w" "-Ofast" "-DNDEBUG")
    endif()
elseif(CMAKE_CXX_COMILER_ID STREQUAL "MSVC")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(compiler_flags "/Zi" "/Od" "/W4" "/WX" "/DDEBUG")
    else()
        set(compiler_flags "/O2" "/GL" "/w" "/DNDEBUG")
    endif()
endif()

## Directories
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(TST_DIR ${CMAKE_SOURCE_DIR}/tst)

add_library(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}
    PRIVATE
    ${compiler_flags})

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRC_DIR}/print.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${INC_DIR})

if(${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(${TST_DIR})
endif()
