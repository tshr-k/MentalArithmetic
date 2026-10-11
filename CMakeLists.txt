cmake_minimum_required(VERSION 3.20)
project(MentalArithmetic)

add_executable(mental_arithmetic
    src/main.cpp
    src/IO.cpp
    src/Number.cpp
    src/Operation.cpp
    src/Problem.cpp
    src/ProblemAttempt.cpp
    src/ProblemGenerator.cpp
    src/Session.cpp
)

target_include_directories(mental_arithmetic PRIVATE include)
target_compile_features(mental_arithmetic PRIVATE cxx_std_23)