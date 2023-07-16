#include <search/example_problems/grid_problem.hpp>
#include <search/breadth_first_search.hpp>
#include <search/depth_first_search.hpp>
#include <search/uniform_cost_search.hpp>

#include <iostream>
#include <functional>

using namespace std;
using namespace search;
using namespace search::example_problems;

void execute_search_experiment(const GridProblem &problem, const auto search) {
    auto found_solution = search(problem);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;
    cout << "Depth of search: " << found_solution.value()->depth << endl; 
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 100,
        .cols = 100,
        .initial = GridEntry { .row=85, .col=99},
        .goal = GridEntry { .row=30, .col=5 }});
    
    cout << "Executing breadth first search..." << endl;
    execute_search_experiment(problem, breadth_first_search<GridProblem>);
    cout << endl;

    cout << "Executing depth first search..." << endl;
    execute_search_experiment(problem, depth_first_search<GridProblem>);
    cout << endl;

    cout << "Executing uniform cost search..." << endl;
    execute_search_experiment(problem, uniform_cost_search<GridProblem>);
    cout << endl;
}
