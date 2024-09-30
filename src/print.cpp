#include "jac/print.hpp"

#include <sstream>
#include <charconv>

namespace
{

auto get_index(const std::string_view str, std::vector<bool>& used) -> size_t
{
    size_t index = 0;

    if (used.empty())
        throw std::runtime_error("Invalid format string, no arguments provided.");

    if (!str.empty())
    {
        auto [_, ec] =
            std::from_chars(
                str.data(),
                str.data() + str.size(),
                index,
                10);

        if (ec != std::errc())
            throw std::runtime_error(
                "Invalid format string, expected integer got \""
                + std::string(str) +
                "\".");
    } else
    {
        while (used[index])
            ++index;
    }

    if (index >= used.size())
        throw std::runtime_error(
            "Invalid format string, index out of bounds: "
            + std::to_string(index) +
            " >= " +
            std::to_string(used.size()));

    used[index] = true;

    return index;
}

auto create_formatted_string(
    const std::string_view format_string,
    const std::vector<std::string>& values,
    std::unique_ptr<std::vector<bool>> used = nullptr
    ) -> std::string
{
    if (!used)
        used = std::make_unique<std::vector<bool>>(values.size(), false);

    const size_t begin = format_string.find_first_of('{');
    const size_t end = format_string.find_first_of('}');

    if(begin == std::string::npos && end == std::string::npos)
        return std::string(format_string);

    if (begin < end)
    {
        if (format_string[begin + 1] == '{')
            return
                std::string(format_string.substr(0, begin + 1))
                + create_formatted_string(
                    format_string.substr(begin + 2),
                    values,
                    std::move(used));
        else
        {
            const size_t index = get_index(
                format_string.substr(begin + 1, end - begin - 1),
                *used);

            return
                std::string(format_string.substr(0, begin))
                + values[index]
                + create_formatted_string(
                    format_string.substr(end + 1),
                    values,
                    std::move(used));
        }
    } else
    {
        if (format_string[end + 1] == '}')
            return
                std::string(format_string.substr(0, end + 1))
                + create_formatted_string(
                    format_string.substr(end + 2),
                    values,
                    std::move(used));
        else
            throw std::runtime_error("Invalid format string, unexpected '}'.");
    }
}

} // namespace

namespace jac
{

using namespace impl;

JAC_IMPL
auto LogLevelCurrent() -> LogLevel&
{
    static LogLevel current = Debug ? LogLevel::Debug : LogLevel::Info;

    return current;
}

template <LogLevel Level, bool PrintLocation>
JAC_IMPL
auto print(
    czstring format_string,
    const print_args args,
    std::ostream& stream,
    const std::source_location location
    ) -> void
{
    if constexpr(Level == LogLevel::Debug && !Debug)
        return;

    if(LogLevelCurrent() > Level)
        return;

    constexpr czstring RESET =  "\033[0m";
    constexpr czstring DIM =    "\033[2m";

    static constexpr std::string_view HEADING =
        Level == LogLevel::Debug ?  "\033[32m[DEBUG]\033[0m " :
        Level == LogLevel::Info  ?  "\033[34m[INFO] \033[0m " :
        Level == LogLevel::Warn  ?  "\033[33m[WARN] \033[0m " :
        Level == LogLevel::Error ?  "\033[31m[ERROR]\033[0m " :
        RESET;
    
    const std::string formatted_string =
        create_formatted_string(
            format_string,
            args.values);

    std::stringstream ss;

    ss << HEADING
        << formatted_string;

    if constexpr(PrintLocation)
        ss << DIM
            << " @ "
            << location.file_name()
            << ":"
            << location.line()
            << RESET;

    ss << "\n";

    stream << ss.str();
}

#define INSTANTIATE_PRINT(Level, PrintLocation) \
    template \
    JAC_IMPL \
    auto print<Level, PrintLocation>( \
        czstring, \
        const print_args, \
        std::ostream&, \
        const std::source_location) -> void;

    INSTANTIATE_PRINT(LogLevel::Debug, true)
    INSTANTIATE_PRINT(LogLevel::Info,  true)
    INSTANTIATE_PRINT(LogLevel::Warn,  true)
    INSTANTIATE_PRINT(LogLevel::Error, true)
    INSTANTIATE_PRINT(LogLevel::Empty, true)

    INSTANTIATE_PRINT(LogLevel::Debug, false)
    INSTANTIATE_PRINT(LogLevel::Info,  false)
    INSTANTIATE_PRINT(LogLevel::Warn,  false)
    INSTANTIATE_PRINT(LogLevel::Error, false)
    INSTANTIATE_PRINT(LogLevel::Empty, false)

#undef INSTANTIATE_PRINT

} // namespace jac
