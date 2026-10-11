#include "IO.hpp"

#include <array>
#include <concepts>
#include <format>
#include <iostream>
#include <sstream>


std::string IO::to_superscript(int n) {
    std::string s = "";
    for (char c : std::to_string(n)) {
        if (c == '-') s += minus_super;
        else s += digits_super[c - '0'];
    }

    return s;
}

std::string IO::to_subscript(int n) {
    std::string s = "";
    for (char c : std::to_string(n)) {
        if (c == '-') s += minus_super;
        else s += digits_sub[c - '0'];
    }

    return s;
}

std::string IO::to_fraction(int numerator, int denominator) {
    return std::format("{}/{}", to_superscript(numerator), to_subscript(denominator));
}
