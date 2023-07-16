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
    auto solution = search(problem);

    if (solution.status == SolutionStatus::Failed) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    auto node = solution.node;
    cout << "Found state: " << node->state << endl;
    cout << "Cost: " << node->path_cost << endl;
    cout << "Depth of search: " << depth(*node) << endl; 

    cout << "Expanded count: " << solution.expanded_count;
}

int main(int, char *[]) {
    const GridProblem problem({
        .rows = 3,
        .cols = 3,
        .initial = GridEntry { .row=0, .col=0},
        .goal = GridEntry { .row=2, .col=2 }});
    
    cout << "Executing breadth first search..." << endl;
    execute_search_experiment(problem, breadth_first_search<GridProblem>);
    cout << endl;
    cout << endl;

    cout << "Executing depth first search..." << endl;
    execute_search_experiment(problem, depth_first_search<GridProblem>);
    cout << endl;
    cout << endl;

    cout << "Executing uniform cost search..." << endl;
    execute_search_experiment(problem, uniform_cost_search<GridProblem>);
    cout << endl;
    cout << endl;
}
