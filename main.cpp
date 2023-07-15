#include <search/map_problem.hpp>
#include <search/depth_first_search.hpp>
#include <search/breadth_first_search.hpp>

#include <iostream>

using namespace std;
using namespace search;

void execute_depth_first_search() {
    const MapProblem problem({
        .rows = 9,
        .cols = 9,
        .initial = MapEntry { .row=7, .col=2 },
        .goal = MapEntry { .row=0, .col=5 }});

    auto found_solution = depth_first_search(problem);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;
}

void execute_breadth_first_search() {
    const MapProblem problem({
        .rows = 9,
        .cols = 9,
        .initial = MapEntry { .row=7, .col=2 },
        .goal = MapEntry{ .row=0, .col=5 }});

    auto found_solution = breadth_first_search(problem);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;
}

int main(int argc, char *argv[]) {
    cout << "Executing depth first search..." << endl;
    execute_depth_first_search();

    cout << "Executing breadth first search..." << endl;
    execute_breadth_first_search();
}
