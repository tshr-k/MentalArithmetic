#pragma once

#include <chrono>
#include <random>
#include <map>
#include <set>

#include "Number.hpp"
#include "Operation.hpp"
#include "Problem.hpp"


struct OpConfig {
    int max_denom_exp {2};
    int sig_figs {2};
    std::set<DisplayStyle> styles {
        DisplayStyle::Decimal,
        DisplayStyle::ImproperFraction,
        DisplayStyle::ProperFraction
    };
    bool mix_styles {true};

    void validate() const;
};

struct ProblemConfig {    
    std::map<OpType, OpConfig> op_map {
        {OpType::Add, OpConfig {}},
        {OpType::Subtract, OpConfig {}},
        {OpType::Multiply, OpConfig {}},
        {OpType::Divide, OpConfig {}}
    };

    void validate() const;
};

class ProblemGenerator {
private:
    ProblemConfig config_;
    std::mt19937& rng_;

public:
    explicit ProblemGenerator(const ProblemConfig& config, std::mt19937& rng);

    Problem generate() const;
};