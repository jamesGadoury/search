#pragma once

#include "search/helpers.hpp"
#include "search/result.hpp"

#include <optional>
#include <queue>
#include <unordered_map>

namespace search {

namespace best_first {

template<IsProblem ProblemInterface, typename EvalFunction>
Result<ProblemNode<ProblemInterface>> best_first_search(const ProblemInterface &problem, const EvalFunction evaluation_function) {
    using Node = ProblemNode<ProblemInterface>;

    std::shared_ptr<Node> node = std::make_shared<Node>(Node {
        .state = problem.initial_state(),
        .parent = nullptr,
        //! @todo need to have action support "no action"... maybe through optional?
        .action = {},
        .path_cost = 0});
    
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, EvalFunction> frontier(evaluation_function);
    frontier.push(node);

    std::unordered_map<std::string, std::shared_ptr<Node>> reached { { node->state, node }};

    size_t expanded_count = 0;

    while(!frontier.empty()) {
        node = frontier.top();
        frontier.pop();

        if(problem.goal_state() == node->state) return {.status=ProblemStatus::Solved, .node=node, .expanded_count=expanded_count};

        expanded_count += 1;
        for (std::shared_ptr<Node> child : expand(problem, node)) {
            if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return {.status=ProblemStatus::Unsolved, .node=nullptr, .expanded_count=expanded_count};
}

}

}
