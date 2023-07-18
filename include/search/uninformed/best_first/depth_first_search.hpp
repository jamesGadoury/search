#pragma once

#include "search/best_first_search.hpp"

namespace search::uninformed {

namespace best_first {

/**
 * @note Always expands the deepest node in the frontier first. This version of DFS uses
 *       a tree-like structure instead of graph search (which is more memory efficient).
*/
template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> depth_first_search(const ProblemInterface &problem) {
    using Node = ProblemNode<ProblemInterface>;

    const auto compare =
        [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
            return depth(*a) < depth(*b);
        };

    using Compare = decltype(compare);
    return best_first_search<ProblemInterface, Compare>(
        problem,
        compare
    );
}

}

}
