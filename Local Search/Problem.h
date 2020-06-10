#ifndef PROBLEM_H
#define PROBLEM_H

#include <array>
#include <random>

static constexpr unsigned PROBLEM_SIZE = 25;
using board_t = std::array<int, PROBLEM_SIZE>;

template<typename T>
T random(T lower, T upper){
    static std::random_device rand{"default"};
    static std::mt19937 gen{rand()};
    std::uniform_int_distribution<T> dis{lower, upper}; 
    return dis(gen);
}

class Problem {
    public:
        Problem();
        board_t transition(board_t brd);
        bool isGoal(board_t& brd);
        board_t& getInitBoard();
    private:
        board_t init_board;
};

#endif