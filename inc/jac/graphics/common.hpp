/**
 * @file common.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains common graphics API functions and types.
 */
#pragma once

#include "jac/types.hpp"
#include "jac/impl/api.hpp"

namespace jac::graphics
{

/**
 * @brief Enum class for graphics APIs.
 */
enum class API : uint8
{
    OpenGL = 1 << 0,
    // Vulkan = 1 << 1,
    Unknown = 1 << 7  
};

/**
 * @brief Returns the current graphics API. Can be also set to a different value.
 * 
 * @return GraphicsAPI& Reference to the current graphics API.
 */
JAC_API
auto CurrentAPI() -> API&;

/**
 * @brief Initializes the current graphics API.
 * 
 * @return true If the initialization was successful
 */
JAC_API
auto InitAPI() -> bool;

/**
 * @brief Terminates the current graphics API.
 */
JAC_API
auto TerminateAPI() -> void;

/**
 * @brief Enum class for buffer types. By default static buffers are used.
 * 
 * Static - The data is set once and used many times.
 * Dynamic - The data is set many times and used many times.
 * Stream - The data is set once and used at most a few times.
 */
enum class BufferType : uint8
{
    Static = 1 << 0,
    Dynamic = 1 << 1,
    Stream = 1 << 2
};

/**
 * @brief Enum class for memory access types. By default read and write access is used.
 */
enum class AccessType : uint8
{
    Read = 1 << 0,
    Write = 1 << 1,
    ReadWrite = Read | Write
};

} // namespace jac::graphics
