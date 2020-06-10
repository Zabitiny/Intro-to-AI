#include "local_search.h"

board_t simulated_annealing(Problem& prob, int& sc) {
    Node current = Node(prob);
    for(int t=0; t < 100000; t++){
        if(prob.isGoal(current.brd)) {
            sc = t;
            return current.brd;
        }
        auto T = 1/log(t+10);
        if(T <= 0.0) {
            sc = t;
            return current.brd;
        }

        Node next = Node(prob, current);
        auto deltaE = current.value - next.value;
        if(deltaE > 0) {
            current = next;
        }
        else if(exp(deltaE/T) >= (double)rand()/(double)RAND_MAX) {
            current = next;
        }
    }
    sc = 100000;
    return current.brd;
}

board_t reproduce(const Node& x, const Node& y, const unsigned cutoff) {
    board_t brd{};
    for(auto i=0u; i < cutoff; i++) {
        brd[i] = x.brd[i];
    }

    for(auto i=cutoff; i < PROBLEM_SIZE; i++) {
        brd[i] = y.brd[i];
    }
    return brd;
}

board_t genetic(std::vector<Node>&& pop, Problem& prob, int& sc) {
    std::vector<Node> new_pop;
    auto n = pop.size();
    new_pop.reserve(n);
    for(int generation=0; generation < 1000; generation++) {
        std::sort(pop.begin(), pop.end());
        if(prob.isGoal(pop.at(0).brd)) {
            sc = generation * n;
            return pop.at(0).brd;
        }

        for(auto i=0u; i < n; i++) {
            Node x = pop.at(random<int>(0, 3*n/20));
            Node y = pop.at(random<int>(0, 3*n/20));
            board_t child_brd = reproduce(x, y, random<int>(1, PROBLEM_SIZE-2));
            
            if(x.value == y.value) child_brd = prob.transition(child_brd);
            
            new_pop.emplace_back(child_brd);
        }
        pop = new_pop;
        new_pop.clear();
    }
    std::sort(pop.begin(), pop.end());
    sc = 1000*pop.size();
    return pop.at(0).brd;
}