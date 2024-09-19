cmake_minimum_required(VERSION 3.29)

project(JacLib)

## Options
option(${PROJECT_NAME}_BUILD_TESTS "Build tests" OFF)
option(${PROJECT_NAME}_GRAPHICS "Enable graphics support" ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(CMAKE_BUILD_TYPE "Build type" Release)

## Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Set compiler flags based on compiler and build type
set(compiler_flags "")

## GCC/Clang flags are set by CMAKE_BUILD_TYPE
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(compiler_flags "-g" "-O0" "-Wall" "-Wextra" "-Wpedantic" "-Werror" "-DDEBUG")
    else()
        set(compiler_flags "-w" "-Ofast" "-DNDEBUG")
    endif()
endif()

## MSVC flags are set by --config=Release/Debug
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi /DDEBUG /W4 /WX")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL")
endif()

## Directories
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(TST_DIR ${CMAKE_SOURCE_DIR}/tst)

## Get Dependencies
add_subdirectory(${VENDOR_DIR})

## Define library
add_library(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}
    PRIVATE
    ${compiler_flags})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    JACLIB_BUILD_LIB)

if(BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)

    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        JACLIB_SHARED_LIB)
endif()

if(${PROJECT_NAME}_GRAPHICS)
    ## For now only OpenGL is supported
    find_package(OpenGL REQUIRED)

    if (NOT OPENGL_FOUND)
        message(FATAL_ERROR "OpenGL not found")
    endif()

    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        JACLIB_GRAPHICS)

    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        OpenGL::GL
        GLAD
        glfw)

    target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}/graphics/window.cpp)
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRC_DIR}/print.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${INC_DIR})

## Tests
if(${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(${TST_DIR})
endif()

### Remove later

add_executable(exec main.cpp)

target_link_libraries(exec
    PRIVATE
    ${PROJECT_NAME})
