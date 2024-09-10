#include <gtest/gtest.h>

#include <array>
#include <tuple>
#include <algorithm>

#include "jac/print.hpp"
#include "jac/types.hpp"

namespace
{

auto strings_equal(
    const std::string_view l,
    const std::string_view r) -> bool
{
    return l.compare(r) == 0;
}

template <size_t I = 0, typename Tuple, typename Arr>
auto test_tuple(
    const Tuple& values,
    const Arr& expected
) -> void
{
    if constexpr (I >= std::tuple_size_v<Tuple>)
        return;
    else
    {
        using T = std::tuple_element_t<I, Tuple>;

        const T& val = std::get<I>(values);

        constexpr czstring RESET = "\033[0m";
        constexpr czstring HEADING = RESET;

        const std::string str = std::string()
            + HEADING
            + expected[I]
            + "\n";

        std::ostringstream stream;

        jac::print_simple("{}", val, stream);

        const std::string result = stream.str();

        EXPECT_TRUE(strings_equal(result, str));

        test_tuple<I + 1>(values, expected);
    }
}

auto string_contains(
    const std::string_view str,
    const std::string_view substr
) -> bool
{
    return str.find(substr) != std::string::npos;
}

} // namespace

TEST(Print, DifferentTypes)
{
    struct string_convertible
    {
        operator std::string() const
        { return "string_convertible"; }
    };
    
    const std::tuple values = std::make_tuple(
        bool{true},
        char{'a'},
        short{1},
        int{-2},
        long{3},
        float{4.0},
        double{5.0},
        uint{6u},
        std::string{"string"},
        std::string_view{"string_view"},
        czstring{"czstring"},
        string_convertible{});

    const std::array<std::string,12> expected = {
        "true",
        "a",
        "1",
        "-2",
        "3",
        "4.000000",
        "5.000000",
        "6",
        "string",
        "string_view",
        "czstring",
        "string_convertible"
    };

    test_tuple(values, expected);
}

TEST(Print, SourceLocation)
{
    std::ostringstream stream;

    jac::print("", {}, stream);

    constexpr int line = __LINE__ - 2;
    constexpr czstring file = __FILE__;

    const std::string str = stream.str();

    EXPECT_TRUE(
        string_contains(str, std::to_string(line)));
    EXPECT_TRUE(
        string_contains(str, file));
}

TEST(Print, LogLevels)
{
    using namespace jac;

    LogLevelCurrent() = LogLevel::Debug;

    std::ostringstream stream;

    stream.str  (std::string());
    print_debug ("", {}, stream);

    if (Debug)
        EXPECT_TRUE (string_contains(stream.str(), "[DEBUG]"));

    stream.str  (std::string());
    print_info  ("", {}, stream);
    EXPECT_TRUE (string_contains(stream.str(), "[INFO]"));

    stream.str  (std::string());
    print_warn  ("", {}, stream);
    EXPECT_TRUE (string_contains(stream.str(), "[WARN]"));

    stream.str  (std::string());
    print_error ("", {}, stream);
    EXPECT_TRUE (string_contains(stream.str(), "[ERROR]"));

    LogLevelCurrent() = LogLevel::Info;

    stream.str  (std::string());
    print_debug ("", {}, stream);
    EXPECT_TRUE (stream.str().empty());

    LogLevelCurrent() = LogLevel::Warn;

    stream.str  (std::string());
    print_debug ("", {}, stream);
    print_info  ("", {}, stream);
    EXPECT_TRUE (stream.str().empty());

    LogLevelCurrent() = LogLevel::Error;

    stream.str  (std::string());
    print_debug ("", {}, stream);
    print_info  ("", {}, stream);
    print_warn  ("", {}, stream);
    EXPECT_TRUE (stream.str().empty());

    LogLevelCurrent() = LogLevel::Empty;

    stream.str  (std::string());
    print_debug ("", {}, stream);
    print_info  ("", {}, stream);
    print_warn  ("", {}, stream);
    print_error ("", {}, stream);
    EXPECT_TRUE (stream.str().empty());

    print_simple("", {}, stream);
    EXPECT_FALSE(stream.str().empty());
}
