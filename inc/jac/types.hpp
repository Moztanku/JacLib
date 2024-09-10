/**
 * @file types.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains common type aliases, some inspired by C++ core guidelines.
 */
#pragma once

#include <memory>
#include <cstdint>

// Integer types
using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;

using int8      = int8_t;
using int16     = int16_t;
using int32     = int32_t;
using int64     = int64_t;

using uint8     = uint8_t;
using uint16    = uint16_t;
using uint32    = uint32_t;
using uint64    = uint64_t;

// Floating point types
using float32  = float;
using float64  = double;

// String types
using zstring   = char*;
using czstring  = const char*;

// Pointer types
template <typename T>
using owner = T*;

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// Aliases for std functions
using std::make_unique;
using std::make_shared;

using std::move;
using std::forward;
