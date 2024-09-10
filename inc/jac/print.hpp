/**
 * @file print.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains various print functions for logging.
 *      They have different log levels and can print the source location.
 *      They also support string formatting.
 */
#pragma once

#include <iostream>
#include <source_location>

#include "jac/debug.hpp"
#include "jac/types.hpp"

#include "jac/impl/print_args.hpp"

namespace jac
{

/**
 * @brief Enum class for log levels.
 */
enum class LogLevel : uint8
{
    Debug   = 1 << 0,
    Info    = 1 << 1,
    Warn    = 1 << 2,
    Error   = 1 << 3,
    Empty   = 1 << 4
};

/**
 * @brief Returns the current log level. Can be also set to a different value.
 * 
 * @return LogLevel& Reference to the current log level.
 */
inline auto LogLevelCurrent() -> LogLevel&
{
    static LogLevel current = Debug ? LogLevel::Debug : LogLevel::Info;

    return current;
}

/**
 * @brief Prints a formatted string with the given arguments.
 * 
 * @tparam Level The log level of the message.
 * @tparam PrintLocation Whether to print the source location.
 * 
 * @param format_string The format string to print. Example: "Hello, {}!"
 * @param args The arguments to insert into the format string. Example: {"World"}
 * @param stream The stream to print to. Default is std::cout.
 * @param location The source location of the print statement. Can be ignored as it is automatically filled.
 *
 *  The format string can contain placeholder in the form of "{}" or "{index}" where index is an unsigned integer.
 *  The index specifies the index of the argument to be inserted at that position. If no index is specified,
 *  the next unused argument is used.
 *  
 *  If Level is set to a level lower than LogLevelCurrent, or LogLevelCurrent is equal to Debug and Debug is false
 *  the print statement is ignored.
 * 
 *  To print curly braces, use double curly braces "{{" and "}}".
 * 
 *  Example:
 *  @code {.cpp}
 *  jac::print("Hello, {}!", {"World"});
 *  jac::print("{0} + {1} = {2}", {1, 2, 3});
 *  jac::print<LogLevel::Info, false>(
 *      "vec.size() = {3}, vec = {{ {} {} {} }}",
 *      {
 *          vec[0],
 *          vec[1],
 *          vec[2],
 *          vec.size()
 *      }
 *  );
 *  jac::print_debug  ("This uses debug alias.");
 *  jac::print_info   ("This uses info alias.");
 *  jac::print_warn   ("This uses warn alias.");
 *  jac::print_error  ("This uses error alias.");
 *  jac::print_simple ("This will print only this message.");
 *  @endcode
 */
template <LogLevel Level = LogLevel::Empty, bool PrintLocation = true>
auto print(
    czstring format_string,
    const impl::print_args args = {},
    std::ostream& stream = std::cout,
    const std::source_location location = std::source_location::current()
) -> void;

// Aliases for different log levels, they are just wrappers around the print function.

/**
 * @brief Prints without any [INFO] or [DEBUG] prefix. Also ignores LogLevelCurrent and doesn't print the source location.
 */
const auto print_simple = [](
    czstring fmt,
    const impl::print_args args = {},
    std::ostream& stream = std::cout,
    const std::source_location loc = std::source_location::current())
{
    print<LogLevel::Empty, false>(fmt, args, stream, loc);
};

/**
 * @brief Prints with [DEBUG] prefix. Ignores LogLevelCurrent if it is higher than Debug or if DEBUG is defined.
 */
const auto print_debug = [](
    czstring fmt,
    const impl::print_args args = {},
    std::ostream& stream = std::cout,
    const std::source_location loc = std::source_location::current())
{
    print<LogLevel::Debug>(fmt, args, stream, loc);
};

/**
 * @brief Prints with [INFO] prefix. Ignores LogLevelCurrent if it is higher than Info.
 */
const auto print_info = [](
    czstring fmt,
    const impl::print_args args = {},
    std::ostream& stream = std::cout,
    const std::source_location loc = std::source_location::current())
{
    print<LogLevel::Info>(fmt, args, stream, loc);
};

/**
 * @brief Prints with [WARN] prefix. Ignores LogLevelCurrent if it is higher than Warn.
 */
const auto print_warn = [](
    czstring fmt,
    const impl::print_args args = {},
    std::ostream& stream = std::cout,
    const std::source_location loc = std::source_location::current())
{
    print<LogLevel::Warn>(fmt, args, stream, loc);
};

/**
 * @brief Prints with [ERROR] prefix. Ignores LogLevelCurrent only if it's set to LogLevel::Empty, also prints to std::cerr instead of std::cout.
 */
const auto print_error = [](
    czstring fmt,
    const impl::print_args args = {},
    std::ostream& stream = std::cerr,
    const std::source_location loc = std::source_location::current())
{
    print<LogLevel::Error>(fmt, args, stream, loc);
};

} // namespace jac
