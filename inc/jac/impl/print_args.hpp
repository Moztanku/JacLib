#pragma once

#include <vector>
#include <string>

namespace jac::impl
{

template <typename T>
concept string_convertible = requires (T& value)
{
    std::string(value);
};

struct print_args
{
    using value_type = std::string;

    template <typename T>
    static auto convert_arg(const T& arg) -> value_type
    {
        if constexpr(string_convertible<T>)
            return std::string(arg);
        else if constexpr(std::is_arithmetic_v<T>)
            return std::to_string(arg);
        else
            static_assert(
                false,
                "Unsupported type for print_args, provide string conversion.");
    }

    template <typename... Args>
    print_args(const Args&... args)
        : values{convert_arg(args)...}
    {}

    const std::vector<value_type> values;
};

} // namespace jac::impl
