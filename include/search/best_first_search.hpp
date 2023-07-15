#pragma once

#include "search/problem.hpp"

#include <optional>
#include <queue>
#include <unordered_map>

namespace search {

// Temporary proto code -> state is encoded as a string...

//! @todo make into generator iterator...

template <IsProblem Problem>
std::vector<std::shared_ptr<typename Problem::Node>> expand(const std::shared_ptr<Problem> &problem, const std::shared_ptr<const typename Problem::Node> &node) {
    std::vector<std::shared_ptr<typename Problem::Node>> nodes;

    for (const auto &action : problem->actions(node->state)) {
        const std::string next_state = problem->results(node->state, action);
        const auto cost = node->path_cost + problem->action_cost(node->state, action, next_state);

        nodes.push_back(std::make_shared<typename Problem::Node>(typename Problem::Node{.state=next_state, .parent=const_pointer_cast<typename Problem::Node>(node), .action=action, .path_cost=cost}));
    }

    return nodes;
}

template<IsProblem Problem, typename EvalFunction>
std::optional<std::shared_ptr<typename Problem::Node>> best_first_search(const std::shared_ptr<Problem> problem, const EvalFunction evaluation_function) {
    std::shared_ptr<typename Problem::Node> node = problem->initial_node();

    std::priority_queue<std::shared_ptr<typename Problem::Node>, std::vector<std::shared_ptr<typename Problem::Node>>, EvalFunction> frontier(evaluation_function);
    frontier.push(node);

    std::unordered_map<std::string, std::shared_ptr<typename Problem::Node>> reached { { node->state, node }};

    while(!frontier.empty()) {
        node = frontier.top();
        frontier.pop();

        if(problem->goal_node()->state == node->state) return node;

        for (const std::shared_ptr<typename Problem::Node> &child : expand(problem, node)) {
            if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return std::nullopt;
}

}
