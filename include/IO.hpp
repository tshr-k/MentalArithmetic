#pragma once

#include <array>
#include <concepts>
#include <format>
#include <iostream>
#include <sstream>

namespace IO {
    template<typename T>
    concept OStreamable = requires (T x, std::ostream& os) {
        {os << x} -> std::same_as<std::ostream&>;
    };

    template<typename T>
    std::string to_string(const T& obj) {
        std::ostringstream oss;
        oss << obj;
        return oss.str();
    }

    constexpr std::array<const char*, 10> digits_super {
        "⁰", "¹", "²", "³", "⁴",
        "⁵", "⁶", "⁷", "⁸", "⁹"
    };

    constexpr std::array<const char*, 10> digits_sub {
        "₀", "₁", "₂", "₃", "₄",
        "₅", "₆", "₇", "₈", "₉"
    };

    constexpr std::string_view minus_super = "⁻";

    std::string to_superscript(int n);
    std::string to_subscript(int n);
    std::string to_fraction(int numerator, int denominator);
}