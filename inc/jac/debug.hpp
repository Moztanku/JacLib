/**
 * @file debug.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief Defines the Debug constant, enabled by -DDEBUG.
 */
#pragma once

#ifdef DEBUG
    constexpr bool Debug {true};
#else
    constexpr bool Debug {false};
#endif
