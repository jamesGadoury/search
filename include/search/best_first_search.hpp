#pragma once

#include "search/problem.hpp"

#include <optional>
#include <queue>
#include <unordered_map>

namespace search {

// Temporary proto code -> state is encoded as a string...

//! @todo make into generator iterator...

template <IsProblem ProbemInterface>
std::vector<std::shared_ptr<typename ProbemInterface::Node>> expand(const ProbemInterface &problem, const std::shared_ptr<const typename ProbemInterface::Node> &node) {
    std::vector<std::shared_ptr<typename ProbemInterface::Node>> nodes;

    for (const auto &action : problem.actions(node->state)) {
        const std::string next_state = problem.results(node->state, action);
        const auto cost = node->path_cost + problem.action_cost(node->state, action, next_state);

        nodes.push_back(std::make_shared<typename ProbemInterface::Node>(typename ProbemInterface::Node{.state=next_state, .parent=const_pointer_cast<typename ProbemInterface::Node>(node), .action=action, .path_cost=cost}));
    }

    return nodes;
}

template<IsProblem ProbemInterface, typename EvalFunction>
std::optional<std::shared_ptr<typename ProbemInterface::Node>> best_first_search(const ProbemInterface &problem, const EvalFunction evaluation_function) {
    std::shared_ptr<typename ProbemInterface::Node> node = problem.initial_node();

    std::priority_queue<std::shared_ptr<typename ProbemInterface::Node>, std::vector<std::shared_ptr<typename ProbemInterface::Node>>, EvalFunction> frontier(evaluation_function);
    frontier.push(node);

    std::unordered_map<std::string, std::shared_ptr<typename ProbemInterface::Node>> reached { { node->state, node }};

    while(!frontier.empty()) {
        node = frontier.top();
        frontier.pop();

        if(problem.goal_node()->state == node->state) return node;

        for (const std::shared_ptr<typename ProbemInterface::Node> &child : expand(problem, node)) {
            if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return std::nullopt;
}

}
