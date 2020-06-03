#include "Problem.h"

Problem::Problem() {
    for(int& i : init_board) {
        i = random<int>(0, PROBLEM_SIZE-1);
    }
    update_constraints(init_board);
}

void Problem::update_constraints(const board_t& brd) {
    std::unordered_map<unsigned, std::set<unsigned>> umap;
    for(auto i=0u; i < PROBLEM_SIZE-1; i++) {
        std::set<unsigned> set;
        for(auto j=i+1; j < PROBLEM_SIZE; j++) {
            auto deltaI = j-i;
            unsigned deltaQ = abs(brd[i] - brd[j]);
            if((brd[i] == brd[j] || deltaI == deltaQ)) {
                set.insert(j);
            }
        }
        umap[i] = set;
    }

    constraints.clear();
    for(const auto& conflict_group : umap){
        constraints.push_back(conflict_group.first);
        for(const auto & column : conflict_group.second){
            constraints.push_back(column);
        }
    }
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