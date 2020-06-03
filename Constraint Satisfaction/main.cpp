#include "constrained_search.h"

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

int main() {
    using namespace std::chrono;
    using millis_frac_t = duration<double, std::milli>;

    std::cout << "Three sample solutions for min conflicts:" << std::endl;
    auto MAX_STEPS = 1000;
    for(int i=1; i <= 3; i++) {
        bool is_goal = false;
        std::cout << i << ") ";
        while(!is_goal) {
            Problem prob{};
            board_t b = min_conflicts(prob, MAX_STEPS);
            
            if(prob.isGoal(b)){
                is_goal = true;
                print_board(b);
            }
        }
    }
    
    std::cout << "Running 1000 tests and calculating results for min conflicts: " << std::endl;

    std::vector<board_t> solved;
    std::vector<millis_frac_t> times;

    for(auto i=0; i < 1000; i++){
        Problem prob{};
        auto start = high_resolution_clock::now();
        board_t b = min_conflicts(prob, MAX_STEPS);
        auto finish = high_resolution_clock::now();
        times.push_back(duration_cast<millis_frac_t>(finish - start));
        
        if(prob.isGoal(b)) {
            solved.push_back(b);
        }
    }
    std::cout << "Max steps: " << MAX_STEPS << std::endl;
    std::cout << "percentage of solved problems: " << solved.size()/1000.0 << std::endl;

    millis_frac_t total{0.0};
    for(auto & i : times) {
        total += i;
    }
    std::cout << "average run time of 1000 instances of min conflicts: " << total.count()/1000.0 << " ms" << std::endl;

    return 0;
}