#include <search/map_problem.hpp>
#include <search/best_first_search.hpp>

#include <iostream>

using namespace std;
using namespace search;

int main(int argc, char *argv[]) {
    const shared_ptr<MapProblem::ProblemType> problem = make_shared<MapProblem>(MapProblemConfig{.rows=9,.cols=9,.initial=MapEntry{.row=7,.col=2},.goal=MapEntry{.row=0,.col=5}});

    auto cmp = [](shared_ptr<MapProblem::Node> a, shared_ptr<MapProblem::Node> b) {return a->path_cost < b->path_cost; };
    auto found_solution = best_first_search(problem, cmp);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return -1;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;

}
