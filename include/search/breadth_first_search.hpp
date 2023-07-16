#pragma once

#include "search/result.hpp"
#include "search/helpers.hpp"

#include <optional>
#include <queue>
#include <unordered_map>

namespace search {

/**
 * @note This algorithm is "cost optimal" for problems where all actions have the same cost. It will
 *       always find the result with the minimum number of actions.
*/
template<IsProblem ProblemInterface>
Result<NodeTemplate<ProblemInterface>> breadth_first_search(const ProblemInterface &problem) {
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

    size_t expanded_count = 0;
    while(!frontier.empty()) {
        node = frontier.front();
        frontier.pop();

        expanded_count += 1;
        for (std::shared_ptr<Node> child : expand(problem, node)) {
            if(problem.goal_state() == child->state) return {.status=ProblemStatus::Solved, .node=child, .expanded_count=expanded_count};

            if(!reached.contains(child->state)) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return {.status=ProblemStatus::Unsolved, .node=nullptr, .expanded_count=expanded_count};
}

}
