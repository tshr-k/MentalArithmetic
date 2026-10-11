#include "ProblemGenerator.hpp"

#include <cmath>
#include <chrono>
#include <random>
#include <stdexcept>
#include <vector>

#include "Number.hpp"
#include "Operation.hpp"
#include "Problem.hpp"


void OpConfig::validate() const {
    if (sig_figs < 1) {
        throw std::invalid_argument("OpConfig: `sig_figs` cannot be < 1");
    }

    if (styles.empty()) {
        throw std::invalid_argument("OpConfig: `styles` cannot be empty");
    }
}

void ProblemConfig::validate() const {
    if (op_map.empty()) {
        throw std::invalid_argument("ProblemConfig: `ops` cannot be empty");
    }

    for (const auto& [_, op_config] : op_map) {
        op_config.validate();
    }
}

ProblemGenerator::ProblemGenerator(const ProblemConfig& config, std::mt19937& rng) : config_{config}, rng_{rng} {
    config_.validate();
}

Problem ProblemGenerator::generate() const {
    auto& op_map {config_.op_map};
    std::pair<OpType, OpConfig> op_pair;
    std::sample(op_map.begin(), op_map.end(), &op_pair, 1, rng_);
    auto [op_type, op_config] {op_pair};

    bool is_division = (op_type == OpType::Divide);
    Operation op {is_division ? OpType::Multiply : op_type};

    int sig_figs {op_config.sig_figs};
    
    std::uniform_int_distribution num_dist {1, static_cast<int>(std::pow(10, sig_figs))-1};
    int a_num {num_dist(rng_)};
    int b_num {num_dist(rng_)};
    
    std::uniform_int_distribution denom_exp_dist {1, op_config.max_denom_exp};
    int a_denom {static_cast<int>(std::pow(10, denom_exp_dist(rng_)))};
    int b_denom {static_cast<int>(std::pow(10, denom_exp_dist(rng_)))};

    Number a {a_num, a_denom};
    Number b {b_num, b_denom};
    Number c {op(a, b)};

    std::uniform_int_distribution mask_target_dist {0, 2};
    MaskTarget mt {static_cast<MaskTarget>(mask_target_dist(rng_))};

    auto& styles {op_config.styles};
    DisplayStyle style_1;
    DisplayStyle style_2;
    
    std::sample(styles.begin(), styles.end(), &style_1, 1, rng_);
    if (op_config.mix_styles) {
        std::sample(styles.begin(), styles.end(), &style_2, 1, rng_);
    } else {
        style_2 = style_1;
    }


    Problem p {
        a, b, c, op, mt, style_1, style_2
    };

    if (is_division) {
        return p.inverse();
    }

    return p;
}