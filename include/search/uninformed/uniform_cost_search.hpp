#pragma once

#include "search/best_first_search.hpp"
#include "search/node.hpp"

namespace search::uninformed {

/**
 * @note This is Dijkstra's Algorithm, which is useful for when actions in the problem have different costs.
*/
template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> uniform_cost_search(
    const ProblemInterface &problem,
    const eventpp::EventDispatcher<Event, void (const ProblemNode<ProblemInterface> &)> *event_dispatcher = nullptr
) {
    using Node = ProblemNode<ProblemInterface>;

    return best_first_search(
        problem,
        [](const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {
            return a->path_cost < b->path_cost;
        },
        event_dispatcher
    );
}

}
