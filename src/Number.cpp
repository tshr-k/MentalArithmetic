#include "IO.hpp"
#include "Number.hpp"

#include <cmath>
#include <format>
#include <iostream>
#include <numeric>
#include <regex>
#include <stdexcept>
#include <string>


Number::Number() : numerator_{0}, denominator_{1} {}

Number::Number(int numerator, int denominator) : numerator_{numerator}, denominator_{denominator} {
    // ensure denominator_ > 0
    if (denominator_ == 0) {
        throw std::domain_error("Number: `denominator` cannot be zero");
    } 
    
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    
    if (int gcd = std::gcd(numerator_, denominator_); gcd != 1) {
        numerator_ /= gcd;
        denominator_ /= gcd;
    }
}

int Number::numerator() const {
    return numerator_;
}

int Number::denominator() const {
    return denominator_;
}

float Number::value() const {
    return static_cast<float>(numerator_) / denominator_;
}

std::string Number::to_string(DisplayStyle style) const {
    switch (style) {
        case DisplayStyle::Decimal:
            return std::format("{:g}", value());
        case DisplayStyle::ProperFraction:
            if (int abs_numerator = abs(numerator_); abs_numerator >= denominator_) {
                int quotient {numerator_ / denominator_};
                int remainder {abs_numerator % denominator_};

                std::string quotient_str = std::to_string(quotient);
                std::string remainder_str = (remainder == 0) ? "" : " " + IO::to_fraction(abs_numerator, denominator_);
                return quotient_str + remainder_str;
            }
            [[fallthrough]];  // proper == improper if abs_numerator < denominator_
        case DisplayStyle::ImproperFraction:
            return IO::to_fraction(numerator_, denominator_);
    }
}

Number operator+(Number a, Number b) {
    return Number {
        a.numerator()*b.denominator() + b.numerator()*a.denominator(),
        a.denominator()*b.denominator()
    };
}

Number operator-(Number a) {
    return Number {
        -a.numerator(),
        a.denominator()
    };
}

Number operator-(Number a, Number b) {
    return a + (-b);
}

Number operator*(Number a, Number b) {
    return Number {
        a.numerator()*b.numerator(),
        a.denominator()*b.denominator()
    };
}

Number operator/(Number a, Number b) {
    return Number {
        a.numerator()*b.denominator(),
        a.denominator()*b.numerator()
    };
}

bool operator==(Number a, Number b) {
    return a.numerator() == b.numerator() && a.denominator() == b.denominator();
}

std::ostream& operator<<(std::ostream& os, Number number) {
    return os << number.to_string(DisplayStyle::Decimal);
}

std::istream& operator>>(std::istream& is, Number& number) {
    std::string input;
    is >> input;
    if (input.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::regex decimal_pattern {R"((-?\d*)\.?(\d*))"};
    std::regex fraction_pattern {R"((-?\d+)/(\d+))"};

    std::smatch matches;

    if (std::regex_match(input, matches, decimal_pattern)) {
        int numerator {std::stoi(matches[1].str() + matches[2].str())};
        int denominator {static_cast<int>(std::pow(10, matches[2].length()))};
        number = Number {numerator, denominator};
    } else if (std::regex_match(input, matches, fraction_pattern)) {
        int numerator {std::stoi(matches[1])};
        int denominator {std::stoi(matches[2])};
        number = Number {numerator, denominator};
    } else {
        is.setstate(std::ios_base::failbit);
    }

    return is;
}