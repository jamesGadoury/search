#include <search/example_problems/grid_problem.hpp>
#include <search/uninformed/breadth_first_search.hpp>
#include <search/uninformed/best_first/breadth_first_search.hpp>
#include <search/uninformed/best_first/depth_first_search.hpp>
#include <search/uninformed/uniform_cost_search.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace search;
using namespace search::uninformed;
using namespace search::example_problems;

void execute_search_experiment(const GridProblem &problem, const auto search) {
    auto result = search(problem);

    if (result.status != ProblemStatus::Solved) { 
        cout << "Unsolved to find result." << endl;
        return;
    } 

    auto node = result.node;
    cout << "Found state: " << node->state << endl;
    cout << "Cost: " << node->path_cost << endl;
    cout << "Depth of solution: " << depth(*node) << endl; 
    cout << "Expanded count in search: " << result.expanded_count << endl;
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 1000,
        .cols = 1000,
        .initial = GridEntry { .row=0, .col=0},
        .goal = GridEntry { .row=839, .col=943 }});

    cout << "Starting state: " << problem.initial_state() << endl;
    cout << "Goal state: " << problem.goal_state() << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing uniform_cost_search..." << endl;
    execute_search_experiment(problem, uniform_cost_search<GridProblem>);
    cout << endl;
    cout << endl;
}
