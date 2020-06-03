#ifndef CONSTRAINED_SEARCH_H
#define CONSTRAINED_SEARCH_H

#include "Problem.h"

// counts conflicting queens of the queen in the given position
unsigned count_conflicts(unsigned pos, const board_t& brd);

/** minimize the amount of conflicts of 
 * the variable in the board */
void minimize_conflicts(unsigned var, board_t& brd);

/** algorithm to solve the Nqueens problem using
 * the minimum conflicts strategy */
board_t min_conflicts(Problem& prob, const unsigned MAX_STEPS);

#endif