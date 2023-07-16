#include "search/helpers.hpp"

#include <optional>
#include <queue>
#include <unordered_map>

namespace search {

/**
 * @note This algorithm is "cost optimal" for problems where all actions have the same cost. It will
 *       always find the solution with the minimum number of actions.
*/
template<IsProblem ProblemInterface>
std::optional<std::shared_ptr<NodeTemplate<ProblemInterface>>> breadth_first_search(const ProblemInterface &problem) {
    using Node = NodeTemplate<ProblemInterface>;
    std::shared_ptr<Node> node = std::make_shared<Node>(Node {
        .state = problem.initial_state(),
        .parent = nullptr,
        //! @todo need to have action support "no action"... maybe through optional?
        .action = {},
        .path_cost = 0});
    
    std::queue<std::shared_ptr<Node>> frontier;
    frontier.push(node);

    std::unordered_map<std::string, std::shared_ptr<Node>> reached { { node->state, node }};

    while(!frontier.empty()) {
        node = frontier.front();
        frontier.pop();

        for (std::shared_ptr<Node> child : expand(problem, node)) {
            if(problem.goal_state() == child->state) return child;

            if(!reached.contains(child->state)) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return std::nullopt;
}

}
