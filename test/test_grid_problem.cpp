#include "doctest.h"

#include <search/example_problems/grid_problem.hpp>

using namespace search::example_problems;

TEST_CASE("Testing GridProblem constructor") {
    auto problem = GridProblem({
        .rows = 10,
        .cols = 10,
        .initial = { .row = 1, .col = 2 },
        .goal = { .row = 3, .col = 5 }
    });

    CHECK(problem.initial_state() == "1,2");
    CHECK(problem.goal_state() == "3,5");
}
