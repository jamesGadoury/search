#pragma once

#include "search/result.hpp"
#include "search/helpers.hpp"

#include <optional>
#include <stack>
#include <unordered_map>

namespace search::uninformed {

/**
 * @note This algorithm is a tree-like depth first search with a limited depth value to specify cutoff.
*/
template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> depth_limited_search(const ProblemInterface &problem, const size_t depth_limit, const std::optional<size_t> cycle_evaluation_depth = std::nullopt) {
    using Node = ProblemNode<ProblemInterface>;

    std::shared_ptr<Node> node = std::make_shared<Node>(Node {
        .state = problem.initial_state(),
        .parent = nullptr,
        //! @todo need to have action support "no action"... maybe through optional?
        .action = {},
        .path_cost = 0});
    
    std::stack<std::shared_ptr<Node>> frontier;
    frontier.push(node);

    size_t expanded_count = 0;
    while(!frontier.empty()) {
        node = frontier.top();
        frontier.pop();

        if(problem.goal_state() == node->state) return {.status=ProblemStatus::Solved, .node=node, .expanded_count=expanded_count};

        //! @todo Some pseudocode for this algo suggests we have a "cutoff" value and check if we exceeded depth limit to set it.
        //        We might want a more expressive ProblemStatus enumeration for this, but for now we just leave it at "Unsolved" and
        //        return the same value at end of function. In this case, we just use the depth limit to see if we even should attempt
        //        to expand, which achieves a similar purpose.
        if(depth(*node) <= depth_limit && !has_cycle(*node, cycle_evaluation_depth)) {
            expanded_count += 1;
            for (std::shared_ptr<Node> child : expand(problem, node)) {
                frontier.push(child);
            }
        }
    }

    return {.status=ProblemStatus::Unsolved, .node=nullptr, .expanded_count=expanded_count};
}

/**
 * @note This algorithm repeatedly applies depth-limited search with increasing limits in an
 *       attempt to combine the benifits of depth-first and breadth-first search.
*/
template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> iterative_deepening_search(const ProblemInterface &problem, const std::optional<size_t> cycle_evaluation_depth = std::nullopt) {
    for (size_t depth_limit = 0;; ++depth_limit) {
        auto result = depth_limited_search(problem, depth_limit, cycle_evaluation_depth);

        //! @todo Should we make a separate status to delineate between a Cutoff or timeout?
        if (ProblemStatus::Solved == result.status) {
            return result;
        }
    }
}

}
