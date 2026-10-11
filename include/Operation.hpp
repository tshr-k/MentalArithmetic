#pragma once

#include <iostream>

#include "Number.hpp"

enum class OpType {
    Add, Subtract, Multiply, Divide
};

class Operation {
private:
    OpType type_;

public:
    Operation(OpType type);

    Number apply(Number a, Number b) const;
    Number operator()(Number a, Number b) const;

    Operation inverse() const;

    friend std::ostream& operator<<(std::ostream& os, Operation op);
};