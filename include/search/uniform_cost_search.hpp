#include "search/best_first_search.hpp"

namespace search {

template<IsProblem ProbemInterface>
std::optional<std::shared_ptr<typename ProbemInterface::Node>> uniform_cost_search(const ProbemInterface &problem) {
    return best_first_search(
        problem,
        [](std::shared_ptr<typename ProbemInterface::Node> a, std::shared_ptr<typename ProbemInterface::Node> b) {return a->path_cost < b->path_cost; }
    );
}

}