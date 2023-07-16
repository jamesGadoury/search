#pragma once

#include "search/node.hpp"
#include "search/problem.hpp"

namespace search {

//! @todo make into generator iterator...
template <IsProblem ProblemInterface, IsNode Node>
std::vector<std::shared_ptr<Node>> expand(const ProblemInterface &problem, const std::shared_ptr<Node> &node) {
    std::vector<std::shared_ptr<Node>> nodes;

    for (const auto &action : problem.actions(node->state)) {
        auto next_state = problem.result(node->state, action);
        const auto cost = node->path_cost + problem.action_cost(node->state, action, next_state);

        nodes.push_back(std::make_shared<Node>(Node {
            .state = std::move(next_state),
            .parent = node,
            .action = action,
            .path_cost = cost}));
    }

    return nodes;
}

template <IsNode Node>
size_t depth(const Node &node) {
    size_t depth = 0;
    for (std::shared_ptr<Node> parent = node.parent; parent != nullptr; parent = parent->parent) depth += 1;
    return depth;
}

}
