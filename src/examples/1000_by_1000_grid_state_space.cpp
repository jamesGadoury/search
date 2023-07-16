#include <search/example_problems/grid_problem.hpp>
#include <search/breadth_first_search.hpp>
#include <search/best_first/breadth_first_search.hpp>
#include <search/best_first/depth_first_search.hpp>
#include <search/best_first/uniform_cost_search.hpp>
#include <search/iterative_deepening_search.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace search;
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
    cout << "Actions to get to goal: " << endl;
    const auto actions = actions_to_node(*result.node);
    for (const auto &action : actions) {
        cout << action << endl;
    }
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 1000,
        .cols = 1000,
        .initial = GridEntry { .row=0, .col=0},
        .goal = GridEntry { .row=839, .col=943 }});

    cout << "Starting state: " << problem.initial_state() << endl;
    cout << "Goal state: " << problem.goal_state() << endl;

    // cout << "---------------------------------"  << endl;
    // cout << "Executing breadth_first_search..." << endl;
    // execute_search_experiment(problem, breadth_first_search<GridProblem>);
    // cout << endl;

    // cout << "---------------------------------"  << endl;
    // cout << "Executing best_first::breadth_first_search..." << endl;
    // execute_search_experiment(problem, best_first::breadth_first_search<GridProblem>);
    // cout << endl;

    // cout << "---------------------------------"  << endl;
    // cout << "Executing best_first::depth_first_search..." << endl;
    // execute_search_experiment(problem, best_first::depth_first_search<GridProblem>);
    // cout << endl;
    // cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing iterative_deepening_search..." << endl;
    execute_search_experiment(problem, iterative_deepening_search<GridProblem>);
    cout << endl;
    cout << endl;

    // cout << "---------------------------------"  << endl;
    // cout << "Executing best_first::uniform_cost_search..." << endl;
    // execute_search_experiment(problem, best_first::uniform_cost_search<GridProblem>);
    // cout << endl;
    // cout << endl;
}
