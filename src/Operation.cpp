#include "Operation.hpp"

#include <stdexcept>

#include "Number.hpp"


Operation::Operation(OpType type) : type_{type} {}

Number Operation::apply(Number a, Number b) const {
    switch (type_) {
        case OpType::Add:
            return a + b;
        case OpType::Subtract:
            return a - b;
        case OpType::Multiply:
            return a * b;
        case OpType::Divide:
            return a / b;
    }
    throw std::invalid_argument("Operation::apply: OpType `type` not supported");
}

Number Operation::operator()(Number a, Number b) const {
    return apply(a, b);
}

Operation Operation::inverse() const {
    switch (type_) {
        case OpType::Add:
            return Operation {OpType::Subtract};
        case OpType::Subtract:
            return Operation {OpType::Add};
        case OpType::Multiply:
            return Operation {OpType::Divide};
        case OpType::Divide:
            return Operation {OpType::Multiply};
    }
}

std::ostream& operator<<(std::ostream& os, Operation op) {
    switch (op.type_) {
        case OpType::Add:
            return os << "+";
        case OpType::Subtract:
            return os << "-";
        case OpType::Multiply:
            return os << "x";
        case OpType::Divide:
            return os << "/";
    }
}