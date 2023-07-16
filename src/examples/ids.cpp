#include <search/iterative_deepening_search.hpp>
#include <search/example_problems/grid_problem.hpp>

#include <iostream>
#include <functional>

using namespace std;
using namespace search;
using namespace search::example_problems;

void execute_search_experiment(const GridProblem &problem) {
    static constexpr size_t CYCLE_EVALUATION_DEPTH = 3;
    auto result = iterative_deepening_search(problem, CYCLE_EVALUATION_DEPTH);

    if (result.status != ProblemStatus::Solved) { 
        cout << "Unsolved to find result." << endl;
        return;
    } 

    auto node = result.node;
    cout << "Found state: " << node->state << endl;
    cout << "Cost: " << node->path_cost << endl;
    cout << "Depth of solution: " << depth(*node) << endl; 
    cout << "Expanded count in search: " << result.expanded_count << endl;
    cout << "Actions to get to goal: " << endl;
    const auto actions = actions_to_node(*result.node);
    for (const auto &action : actions) {
        cout << action << endl;
    }
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 6,
        .cols = 6,
        .initial = GridEntry { .row=0, .col=0},
        .goal = GridEntry { .row=4, .col=3 }});

    cout << "Starting state: " << problem.initial_state() << endl;
    cout << "Goal state: " << problem.goal_state() << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing ids..." << endl;
    execute_search_experiment(problem);
    cout << endl;
}
