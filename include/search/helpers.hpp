#pragma once

#include "search/node.hpp"
#include "search/problem.hpp"

#include <vector>
#include <list>
#include <set>
#include <optional>

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

template <IsNode Node>
auto actions_to_node(const Node &node) -> std::list<decltype(node.action)> {
    std::list<decltype(node.action)> actions { node.action };
    for (std::shared_ptr<Node> parent = node.parent; parent != nullptr; parent = parent->parent) actions.push_front(parent->action);
    return actions;
}

template <IsNode Node>
bool has_cycle(const Node &node, const std::optional<size_t> evaluation_depth = std::nullopt) {
    std::set<decltype(node.state)> states { node.state };

    size_t depth = 0;
    for (std::shared_ptr<Node> parent = node.parent; parent != nullptr; parent = parent->parent, ++depth) {
        if(evaluation_depth.has_value() && depth > evaluation_depth.value()) {
            // We've reached how deep we want to look for cycles, so we "estimate" there
            // aren't any. Likely a consumer has tuned the evaluation_depth if they
            // are setting it based on the problem's state space.
            return false;
        }
        if (states.contains(parent->state)) {
            return true;
        }
        states.insert(parent->state);
    };
    return false;
}

}
