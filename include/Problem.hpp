#pragma once

#include <iostream>
#include <string>

#include "IO.hpp"
#include "Number.hpp"
#include "Operation.hpp"

enum class MaskTarget {
    a, b, c
};

class Problem {
private:
    Number a_;
    Number b_;
    Number c_;

    Operation op_;
    
    MaskTarget mask_target_;
    DisplayStyle style_1_;
    DisplayStyle style_2_;

public:
    Problem(Number a, Number b, Number c, Operation op, MaskTarget mask, DisplayStyle style_1, DisplayStyle style_2);

    bool check_answer(Number attempt) const;
    
    Problem inverse() const;

    friend std::ostream& operator<<(std::ostream& os, const Problem& problem);
};
