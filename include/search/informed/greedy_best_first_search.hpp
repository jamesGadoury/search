#pragma once

#include "search/uninformed/best_first/best_first_search.hpp"

#include <functional>

namespace search::informed {

template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> greedy_best_first_search(
    const ProblemInterface &problem,
    const std::function<int(const ProblemInterface &problem, const ProblemNode<ProblemInterface>& node)> heuristic
) {
    using Node = ProblemNode<ProblemInterface>;

    const auto compare =
        [&heuristic, &problem](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
            return heuristic(problem, *a) > heuristic(problem, *b);
        };

    using Compare = decltype(compare);
    return uninformed::best_first::best_first_search<ProblemInterface, Compare>(
        problem,
        compare
    );
}

}
