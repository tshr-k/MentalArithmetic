#include "Session.hpp"

#include <format>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "Number.hpp"
#include "Problem.hpp"
#include "ProblemAttempt.hpp"
#include "ProblemGenerator.hpp"


void SessionConfig::validate() const {
    if (num_problems < 1) {
        throw std::invalid_argument("SessionConfig: `num_problems` cannot be < 1");
    }

    if (max_duration.count() < 0) {
        throw std::invalid_argument("SessionConfig: `max_duration` cannot be negative");
    }

    problem_config.validate();
}

SessionLog::SessionLog(const SessionConfig& config) : config{config} {}

std::string SessionLog::results() const {
    int n = config.num_problems;
    return std::format(
        "RESULTS\n"
        "Time used: {0}/{1}\n"
        "Correct: {2}/{6} | Wrong: {3}/{6}\n"
        "Seen but skipped: {4}/{6} | Unseen: {5}/{6}\n"
        "Mark: {7}/{8}\n",
        elapsed_duration,
        config.max_duration,
        num_seen_correct,
        num_seen_wrong,
        num_seen_skipped,
        n - num_seen,
        n,
        mark,
        n * config.correct_mark
    );
}

Session::Session(const SessionConfig& config, std::mt19937 rng)
: config_{config}, generator_{ProblemGenerator{config.problem_config, rng}} {
    config.validate();
}

SessionLog Session::run() {
    std::cout << "BEGIN\n\n";
    SessionLog log {config_};

    while (log.num_seen <= config_.num_problems-1) {
        Problem p = generator_.generate();
        std::cout << p << "\n" << (config_.live_correct ? "   " : "");
        Number attempt;
        if (std::cin >> attempt) {
            bool is_correct = p.check_answer(attempt);
            if (config_.live_correct) {
                std::cout << (is_correct ? "\x1b[F🟢" : "\x1b[F🔴");
            }
            ++log.num_seen_attempted;
            log.num_seen_correct += is_correct;
            log.num_seen_wrong += !is_correct;
            log.mark += is_correct ? config_.correct_mark : config_.wrong_mark;
        } else {
            std::cin.clear();
            ++log.num_seen_skipped;
            if (config_.live_correct) std::cout << "\x1b[F⚫";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n\n";
        ++log.num_seen;
    }

    return log;
}