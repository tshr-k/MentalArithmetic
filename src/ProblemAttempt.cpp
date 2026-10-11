#include "ProblemAttempt.hpp"

#include <format>
#include <chrono>
#include <iostream>

#include "Number.hpp"
#include "Problem.hpp"


ProblemAttempt::ProblemAttempt(const Problem& problem, Number attempt, std::chrono::milliseconds solve_duration, std::chrono::seconds elapsed_session_time)
    : problem_{problem}, attempt_{attempt}, solve_duration_{solve_duration}, elapsed_session_time_{elapsed_session_time} {}
