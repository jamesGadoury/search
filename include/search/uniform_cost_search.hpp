#pragma once

#include "search/best_first_search.hpp"
#include "search/node.hpp"

namespace search {

/**
 * @note This is Dijkstra's Algorithm, which is useful for when actions in the problem have different costs.
*/
template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> uniform_cost_search(const ProblemInterface &problem) {
    using Node = ProblemNode<ProblemInterface>;

    const auto compare =
        [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
            return a->path_cost > b->path_cost;
        };

    using Compare = decltype(compare);
    return best_first_search<ProblemInterface, Compare>(
        problem,
        compare
    );
}

}