#include "constrained_search.h"

// counts conflicting queens of the queen in the given position
unsigned count_conflicts(unsigned pos, const board_t& brd) {
    auto counter = 0u;
    for(auto i=0u; i < PROBLEM_SIZE; i++) {
        if(i == pos) continue;
        const unsigned deltaI = abs(pos - i);
        const unsigned deltaQ = abs(brd[i] - brd[pos]);
        if(deltaQ == 0 || deltaI == deltaQ){
            counter++;
        }
    }
    return counter;
}

/** minimize the amount of conflicts of 
 * the variable in the board */
void minimize_conflicts(unsigned var, board_t& brd) {
    auto min = count_conflicts(var, brd);
    const unsigned init_val = brd[var];
    unsigned val = init_val;
    
    for(auto i=0u; i < PROBLEM_SIZE; i++) {
        if(i == init_val) continue;
        brd[var] = i;
        auto conflicts = count_conflicts(var, brd);
        if(conflicts <= min) {
            min = conflicts;
            val = i;
        }
    }
    brd[var] = val;
}

/** algorithm to solve the Nqueens problem using
 * the minimum conflicts strategy */
board_t min_conflicts(Problem& prob, const unsigned MAX_STEPS) {
    auto current = prob.get_init_board();

    for(auto i=0u; i < MAX_STEPS; i++) {
        if(prob.is_goal(current)) return current;

        //variables are columns which is really the indices of the board
        const auto var = prob.constraints.at(random<int>(0, prob.constraints.size()-1));
        minimize_conflicts(var, current);
        prob.update_constraints(current);
    }
    return current;
}