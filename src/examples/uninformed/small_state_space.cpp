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

ostream &operator<<(ostream &os, const Result<ProblemNode<GridProblem>> &search_result) {
    return os
        << "Found state: " << search_result.node->state << endl
        << "Cost: " << search_result.node->path_cost << endl
        << "Depth of solution: " << depth(*search_result.node) << endl
        << "Expanded count in search: " << search_result.expanded_count << endl;
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
    cout << "Executing breadth_first_search..." << endl;
    cout << breadth_first_search(problem) << endl;
    cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing best_first::breadth_first_search..." << endl;
    cout << best_first::breadth_first_search(problem) << endl;
    cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing best_first::depth_first_search..." << endl;
    cout << best_first::depth_first_search(problem) << endl;
    cout << endl;
    cout << endl;

    cout << "---------------------------------"  << endl;
    cout << "Executing uniform_cost_search..." << endl;
    cout << uniform_cost_search(problem) << endl;
    cout << endl;
    cout << endl;
}
