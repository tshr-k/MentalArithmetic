#include "Problem.hpp"

#include <format>
#include <iostream>
#include <string>

#include "IO.hpp"
#include "Number.hpp"
#include "Operation.hpp"


Problem::Problem(Number a, Number b, Number c, Operation op, MaskTarget mask_target, DisplayStyle style_1, DisplayStyle style_2)
    : a_{a}, b_{b}, c_{c}, op_{op}, mask_target_{mask_target}, style_1_{style_1}, style_2_{style_2} {}

bool Problem::check_answer(Number attempt) const {
    switch (mask_target_) {
        case MaskTarget::a:
            return attempt == a_;
        case MaskTarget::b:
            return attempt == b_;
        case MaskTarget::c:
            return attempt == c_;
    }
}

Problem Problem::inverse() const {
    MaskTarget mt;
    switch (mask_target_) {
        case MaskTarget::a:
            mt = MaskTarget::c;   
        case MaskTarget::b:
            mt = MaskTarget::b;   
        case MaskTarget::c:
            mt = MaskTarget::a;   
    }

    return Problem {
        c_, b_, a_, op_.inverse(), mt, style_2_, style_1_
    };
}


std::ostream& operator<<(std::ostream& os, const Problem& p) {
    MaskTarget mt {p.mask_target_};
    std::string_view mask {"?"};

    DisplayStyle style_a {p.style_1_};
    DisplayStyle style_b {p.style_2_};
    DisplayStyle style_c {(mt == MaskTarget::a) ? p.style_1_ : p.style_2_};

    return os << std::format(
        "({}) {} ({}) = {}",
        (mt == MaskTarget::a) ? mask : p.a_.to_string(style_a),
        IO::to_string(p.op_),
        (mt == MaskTarget::b) ? mask : p.b_.to_string(style_b),
        (mt == MaskTarget::c) ? mask : p.c_.to_string(style_c)
    );  
}