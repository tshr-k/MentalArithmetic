#pragma once

#include <iostream>
#include <string>

#include "IO.hpp"

enum class DisplayStyle {
    Decimal, ProperFraction, ImproperFraction
};

class Number {
public:
    Number();
    explicit Number(int numerator, int denominator = 1);

    int numerator() const;
    int denominator() const;

    float value() const;
    std::string to_string(DisplayStyle style) const;

private:
    int numerator_;
    int denominator_;
};

Number operator+(Number a, Number b);
Number operator-(Number a);
Number operator-(Number a, Number b);
Number operator*(Number a, Number b);
Number operator/(Number a, Number b);
bool operator==(Number a, Number b);

std::ostream& operator<<(std::ostream& os, Number number);
std::istream& operator>>(std::istream& is, Number& number);