#include <stdexcept>
#include <windows.h>
#include <iostream>
#include <random>

#include "Number.hpp"
#include "Session.hpp"

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    SessionConfig config;
    for (auto& [op_type, op_config] : config.problem_config.op_map) {
        op_config.sig_figs = 2;
        op_config.styles = { DisplayStyle::Decimal };
    }

    unsigned int seed = 111;
    if (argc > 1) {
        try {
            seed = std::stoi(argv[1]);
        } catch (const std::exception& e) {}
    }

    std::mt19937 rng {seed};
    Session session {config, rng};

    SessionLog log = session.run();
    std::cout << log.results();
}