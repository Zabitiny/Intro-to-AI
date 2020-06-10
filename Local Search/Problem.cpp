#include "Problem.h"

Problem::Problem() {
    for(int& i : init_board) {
        i = random<int>(0, PROBLEM_SIZE-1);
    }
}

board_t Problem::transition(board_t brd) {
    bool distinct = false;
    while(!distinct) {
        auto queen = random<int>(0, PROBLEM_SIZE-1);
        auto position = random<int>(0, PROBLEM_SIZE-1);
        if(brd[queen] != position) {
            distinct = true;
            brd[queen] = position;
        }
    }
    return brd;
}

bool Problem::isGoal(board_t& brd) {
    for(auto i=0u; i < PROBLEM_SIZE-1; i++) {
        for(auto j=i+1; j < PROBLEM_SIZE; j++) {
            auto deltaI = j-i;
            unsigned deltaQ = abs(brd[i] - brd[j]);
            if(brd[i] == brd[j] || deltaI == deltaQ) {
                return false;
            }
        }
    }
    return true;
}

board_t& Problem::getInitBoard() {
    return init_board;
}