#include "local_search.h"

#include <chrono>
#include <iostream>

void print_board(const board_t& brd){
    bool print_comma = false;
    for(const auto& item : brd){
        if(print_comma) std::cout << ", "; 
        else print_comma = true;

        std::cout << item;
    }
    std::cout << std::endl;
}

board_t gen_ran_brd() {
    board_t brd{};
    for(int& i : brd) {
        i = random<int>(0, PROBLEM_SIZE-1);
    }
    return brd;
}

int main() {
    using namespace std::chrono;
    using millis_frac_t = duration<double, std::milli>;

    std::cout << "Three sample solutions for simulated annealing:" << std::endl;

    for(int i=1; i <= 3; i++) {
        bool is_goal = false;
        std::cout << i << ") ";
        while(!is_goal) {
            int sc = 0;
            Problem prob{};
            board_t b = simulated_annealing(prob, sc);
            
            if(prob.isGoal(b)){
                is_goal = true;
                print_board(b);
            }
        }
    }
    
    std::cout << "Three sample solutions for genetic algorithm:" << std::endl;

    for(int i=1; i <= 3; i++) {
        bool is_goal = false;
        std::cout << i << ") ";
        while(!is_goal) {
            
            int sc = 0;
            Problem prob{};
            std::vector<Node> pop;
            for(auto j=0; j < 50; j++) pop.push_back(gen_ran_brd());
            board_t b = genetic(std::move(pop), prob, sc);
            if(prob.isGoal(b)){
                is_goal = true;
                print_board(b);
            }
        }
    }
    std::cout << "Running 1000 tests and calculating results for genetic algorithm: " << std::endl;

    std::vector<board_t> solved;
    std::vector<millis_frac_t> times;
    std::vector<int> searchCosts;

    for(auto i=0; i < 1000; i++){
        Problem prob{};
        const unsigned POP_SIZE = 50;
        std::vector<Node> pop;
        pop.reserve(POP_SIZE);
        for(auto j=0u; j < POP_SIZE; j++) pop.push_back(gen_ran_brd());
        int sc = 0;
        auto start = high_resolution_clock::now();
        board_t b = genetic(std::move(pop), prob, sc);
        auto finish = high_resolution_clock::now();
        times.push_back(duration_cast<millis_frac_t>(finish - start));
        searchCosts.push_back(sc);
        if(prob.isGoal(b)) {
            solved.push_back(b);
        }
        pop.clear();
    }
    
    unsigned count = 0;
    for(int i : searchCosts) {
        count += i;
    }
    std::cout << "average search cost for 1000 instances of genetic: " << count/1000.0 << std::endl;
    std::cout << "percentage of solved problems: " << solved.size()/1000.0 << std::endl;

    millis_frac_t total{0.0};
    for(auto & i : times) {
        total += i;
    }
    std::cout << "average run time of 1000 instances of genetic: " << total.count()/1000.0 << " ms" << std::endl;

    solved.clear();
    times.clear();
    searchCosts.clear();

    std::cout << "Running 1000 tests and calculating results for simulated annealing: " << std::endl;

    for(int i=0; i < 1000; i++){
        Problem prob{};
        int sc = 0;
        auto start = high_resolution_clock::now();
        board_t b = simulated_annealing(prob, sc);
        auto finish = high_resolution_clock::now();
        times.push_back(duration_cast<millis_frac_t>(finish - start));
        searchCosts.push_back(sc);
        
        if(prob.isGoal(b)) {
            solved.push_back(b);
        }
    }
    
    count = 0;
    for(int i : searchCosts) {
        count += i;
    }
    std::cout << "average search cost for 1000 instances of simulated annealing: " << count/1000.0 << std::endl;
    std::cout << "percentage of solved problems: " << solved.size()/1000.0 << std::endl;

    total = millis_frac_t::zero();
    for(auto & i : times) {
        total += i;
    }
    std::cout << "average run time of 1000 instances of simulated annealing: " << total.count()/1000.0 << " ms" << std::endl;

    return 0;
}