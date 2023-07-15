#include "search/best_first_search.hpp"

namespace search {

template <IsProblem ProblemInterface>
class DepthFirstSearch : public BestFirstSearchTemplate<ProblemInterface> {
public:
    using BestFirstSearch = BestFirstSearchTemplate<ProblemInterface>;
    using Node = BestFirstSearch::Node;

    DepthFirstSearch(ProblemInterface problem) : BestFirstSearch(std::move(problem))
    {
    }

    std::optional<std::shared_ptr<Node>> search() { return BestFirstSearch::search(COMPARE); }

private:
    static constexpr auto COMPARE = [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
        return a->depth > b->depth;
    };
};

}
