#include <search/example_problems/grid_problem.hpp>
#include <search/informed/a_star_search.hpp>
#include <search/informed/greedy_best_first_search.hpp>
#include <search/uninformed/uniform_cost_search.hpp>

#include <iostream>
#include <functional>

using namespace std;
using namespace search;
using namespace search::informed;
using namespace search::uninformed;
using namespace search::example_problems;

void execute_uninformed_search_experiment(const GridProblem &problem, const auto search) {
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

ostream &operator<<(ostream &os, const Result<ProblemNode<GridProblem>> &search_result) {
    return os
        << "Found state: " << search_result.node->state << endl
        << "Cost: " << search_result.node->path_cost << endl
        << "Depth of solution: " << depth(*search_result.node) << endl
        << "Expanded count in search: " << search_result.expanded_count << endl;
}

static const function<int(const GridProblem &problem, const ProblemNode<GridProblem> &node)> HEURISTIC =
    [](const auto &problem, const auto &node) {
        auto current = to_grid_entry(node.state);
        auto goal = to_grid_entry(problem.goal_state());

        return abs(static_cast<int>(current.row-goal.row)) + abs(static_cast<int>(current.col-goal.col));
    };

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
    cout << uniform_cost_search(problem) << endl;
    cout << endl;
    cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing greedy_best_first_search..." << endl;
    cout << greedy_best_first_search(problem, HEURISTIC) << endl;
    cout << endl;
    cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing a_star_search..." << endl;
    cout << a_star_search(problem, HEURISTIC) << endl;
    cout << endl;
    cout << endl;
}