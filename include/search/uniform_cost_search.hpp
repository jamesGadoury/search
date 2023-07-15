#include "search/best_first_search.hpp"
#include "search/node.hpp"

namespace search {

template <IsProblem ProblemInterface>
class UniformCostSearch : public BestFirstSearchTemplate<ProblemInterface> {
public:
    using BestFirstSearch = BestFirstSearchTemplate<ProblemInterface>;
    using Node = BestFirstSearch::Node;

    UniformCostSearch(ProblemInterface problem) : BestFirstSearch(std::move(problem))
    {
    }

    std::optional<std::shared_ptr<Node>> search() { return search(COMPARE); }

private:
    static constexpr auto COMPARE = [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
        return a->path_cost < b->path_cost;
    };
};

}
