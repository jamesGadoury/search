#pragma once

#include "search/best_first_search.hpp"

namespace search::uninformed {

namespace best_first {

template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> breadth_first_search(const ProblemInterface &problem) {
    using Node = ProblemNode<ProblemInterface>;

    return best_first_search(
        problem,
        [](const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {
            return depth(*a) < depth(*b);
        }
    );
}

}

}
