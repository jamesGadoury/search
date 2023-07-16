#include "search/best_first_search.hpp"

namespace search {

/**
 * @note Always expands the deepest node in the frontier first.
*/
template<IsProblem ProblemInterface>
std::optional<std::shared_ptr<NodeTemplate<ProblemInterface>>> depth_first_search(const ProblemInterface &problem) {
    const auto compare =
        [](std::shared_ptr<NodeTemplate<ProblemInterface>> a, std::shared_ptr<NodeTemplate<ProblemInterface>> b) {
            return depth(*a) < depth(*b);
        };

    using Compare = decltype(compare);
    return best_first_search<ProblemInterface, NodeTemplate<ProblemInterface>, Compare>(
        problem,
        compare
    );
}

}
