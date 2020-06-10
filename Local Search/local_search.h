#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "Problem.h"

#include <functional>
#include <vector>
#include <random>
#include <algorithm>

struct Node {
    board_t brd;
    int value;

    //initial node constructor
    Node(Problem& prob) : brd{prob.getInitBoard()}, value{count_conflicts()} {}

    //constructor for SA successor nodes
    Node(Problem& prob, Node& node) : brd{prob.transition(node.brd)}, value{count_conflicts()} {}

    //constructor for genetic child nodes
    Node(const board_t& input_board = {}) : brd{input_board}, value{count_conflicts()} {}

    int count_conflicts() const {
        auto counter = 0;
        for(auto i=0u; i < PROBLEM_SIZE-1; i++) {
            for(auto j=i+1; j < PROBLEM_SIZE; j++) {
                int deltaI = j-i;
                auto deltaQ = abs(brd[i] - brd[j]);
                if(brd[i] == brd[j] || deltaI == deltaQ) {
                    counter++;
                }
            }
        }
        return counter;
    }

    friend bool operator<(const Node& lhs, const Node& rhs){
        return lhs.value < rhs.value;
    }
};

board_t simulated_annealing(Problem& prob, int& sc);

board_t reproduce(const Node& x, const Node& y, const unsigned cutoff);

board_t genetic(std::vector<Node>&& pop, Problem& prob, int& sc);

#endif