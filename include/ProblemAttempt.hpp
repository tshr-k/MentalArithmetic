#pragma once

#include <chrono>
#include <iostream>
#include <string>

#include "Number.hpp"
#include "Problem.hpp"

class ProblemAttempt {
public:
    ProblemAttempt(const Problem& problem, Number attempt, std::chrono::milliseconds solve_duration, std::chrono::seconds elapsed_session_time);
    
private:
    Problem problem_;
    Number attempt_;
    std::chrono::milliseconds solve_duration_;
    std::chrono::seconds elapsed_session_time_;
};