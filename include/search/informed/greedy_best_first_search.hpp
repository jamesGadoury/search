#pragma once

#include "search/best_first_search.hpp"

#include <functional>

namespace search::informed {

template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> greedy_best_first_search(
    const ProblemInterface &problem,
    const std::function<int(const ProblemInterface &problem, const ProblemNode<ProblemInterface>& node)> heuristic,
    const eventpp::EventDispatcher<Event, void (const ProblemNode<ProblemInterface> &)> *event_dispatcher = nullptr
) {
    using Node = ProblemNode<ProblemInterface>;

    return best_first_search(
        problem,
        [&heuristic, &problem](const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {
            return heuristic(problem, *a) < heuristic(problem, *b);
        },
        event_dispatcher
    );
}

}
