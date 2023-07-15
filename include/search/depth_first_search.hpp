#include "search/best_first_search.hpp"

namespace search {

template<IsProblem Problem>
std::optional<std::shared_ptr<typename Problem::Node>> depth_first_search(const std::shared_ptr<Problem> problem) {
    return best_first_search(
        problem,
        [](std::shared_ptr<typename Problem::Node> a, std::shared_ptr<typename Problem::Node> b) {return a->path_cost > b->path_cost; }
    );
}

}
