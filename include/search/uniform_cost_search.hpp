#include "search/best_first_search.hpp"
#include "search/node.hpp"

namespace search {

template<IsProblem ProblemInterface>
std::optional<std::shared_ptr<NodeTemplate<ProblemInterface>>> uniform_cost_search(const ProblemInterface &problem) {
    const auto compare =
        [](std::shared_ptr<NodeTemplate<ProblemInterface>> a, std::shared_ptr<NodeTemplate<ProblemInterface>> b) {
            return a->path_cost < b->path_cost;
        };

    using Compare = decltype(compare);
    return best_first_search<ProblemInterface, NodeTemplate<ProblemInterface>, Compare>(
        problem,
        compare
    );
}

}