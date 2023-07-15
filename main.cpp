#include <search/example_problems/grid_problem.hpp>
#include <search/depth_first_search.hpp>
#include <search/uniform_cost_search.hpp>

#include <iostream>

using namespace std;
using namespace search;
using namespace search::example_problems;

void execute_depth_first_search(const GridProblem &problem) {
    auto found_solution = depth_first_search(problem);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;
}

void execute_uniform_cost_search(const GridProblem &problem) {
    auto found_solution = uniform_cost_search(problem);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 100,
        .cols = 100,
        .initial = GridEntry { .row=85, .col=99},
        .goal = GridEntry { .row=0, .col=5 }});

    cout << "Executing depth first search..." << endl;
    execute_depth_first_search(problem);

    cout << "Executing breadth first search..." << endl;
    execute_uniform_cost_search(problem);
}
