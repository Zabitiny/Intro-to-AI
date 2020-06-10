#ifndef PROBLEM_H
#define PROBLEM_H

#include <array>
#include <random>
#include <set>
#include <unordered_map>

/** Constraint Satisfaction Problem (CSP) consists of
 * X: set of all variables in problem
 * D: domain of values that can be applied to variables
 * C: set of constraints 
 * 
 * In this case, X is each index of the board
 * D is all the numbers in the board
 * C is the vector of variables that are constrained*/

static constexpr unsigned PROBLEM_SIZE = 25;
using board_t = std::array<int, PROBLEM_SIZE>;  //X & D

template<typename T>
T random(T lower, T upper){
    static std::random_device rand{"default"};
    static std::mt19937 gen{rand()};
    std::uniform_int_distribution<T> dis{lower, upper}; 
    return dis(gen);
}

class Problem {
    public:
        std::vector<unsigned> constraints;
        
        Problem();
        void update_constraints(const board_t& brd);
        bool is_goal(board_t& brd);
        board_t& get_init_board();

    private:
        board_t init_board;
};

#endif