#pragma once

#include <format>
#include <iostream>
#include <random>
#include <vector>

#include "Number.hpp"
#include "Problem.hpp"
#include "ProblemAttempt.hpp"
#include "ProblemGenerator.hpp"

struct SessionConfig {
    int num_problems {20};
    
    int correct_mark {1};
    int seen_skipped_mark {0};
    int wrong_mark {-1};

    bool live_time {true};
    bool live_correct {true};
    
    std::chrono::seconds max_duration {8 * 60};
    ProblemConfig problem_config {};

    void validate() const;
};

struct SessionLog {
    SessionConfig config;

    int num_seen {0};
    
    int num_seen_attempted {0};
    int num_seen_skipped {0};
    int num_seen_correct {0};
    int num_seen_wrong {0};

    int mark {0};

    std::chrono::seconds elapsed_duration {0};
    std::vector<ProblemAttempt> problem_attempts;

    SessionLog(const SessionConfig& config);

    std::string results() const;
};


class Session {
private:
    SessionConfig config_;
    ProblemGenerator generator_;
public:
    Session(const SessionConfig& config, std::mt19937 rng);

    SessionLog run();
};