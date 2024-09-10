#pragma once

#include <vector>
#include <string>
#include <concepts>

namespace jac::impl
{

template <typename From, typename To>
concept constructible_to = std::constructible_from<To, From>;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

struct print_args
{
    using value_type = std::string;

    template <constructible_to<value_type> T>
    static auto convert_arg(const T& arg) -> value_type
    {
        return value_type(arg);
    }

    template <arithmetic T>
    static auto convert_arg(const T arg) -> value_type
    {
        return std::to_string(arg);
    }

    static auto convert_arg(const bool arg) -> value_type
    {
        return arg ? "true" : "false";
    }

    static auto convert_arg(const char arg) -> value_type
    {
        return value_type(1, arg);
    }

    template <typename... Args>
    print_args(const Args&... args)
        : values{convert_arg(args)...}
    {}

    const std::vector<value_type> values;
};

} // namespace jac::impl
