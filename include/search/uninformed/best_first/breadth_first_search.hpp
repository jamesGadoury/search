#pragma once

#include "search/uninformed/best_first_search.hpp"

namespace search::uninformed {

namespace best_first {

template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> breadth_first_search(const ProblemInterface &problem) {
    using Node = ProblemNode<ProblemInterface>;

    const auto compare =
        [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
            return depth(*a) > depth(*b);
        };

    using Compare = decltype(compare);
    return best_first_search<ProblemInterface, Compare>(
        problem,
        compare
    );
}

}

}
