#pragma once

#include "search/node.hpp"
#include "search/problem.hpp"

#include <optional>
#include <queue>
#include <unordered_map>
#include <functional>

namespace search {

template <IsProblem ProblemInterface>
class BestFirstSearchTemplate {
public:
    using Node = NodeTemplate<ProblemInterface>;

    template <typename EvalFunction>
    std::optional<std::shared_ptr<Node>> search(const EvalFunction eval_function) {
        std::shared_ptr<Node> node = std::make_shared<Node>(Node {
            .state = problem.initial_state(),
            .parent = nullptr,
            //! @todo need to have action support "no action"... maybe through optional?
            .action = {},
            .path_cost = 0,
            .depth = 0});

        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, EvalFunction> frontier(eval_function);
        frontier.push(node);

        std::unordered_map<std::string, std::shared_ptr<Node>> reached { { node->state, node }};

        while(!frontier.empty()) {
            node = frontier.top();
            frontier.pop();

            if(problem.goal_state() == node->state) return node;

            for (std::shared_ptr<Node> child : expand(problem, node)) {
                if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                    reached[child->state] = child;
                    frontier.push(child);
                }
            }
        }

        return std::nullopt;
    }

protected:
    BestFirstSearch(ProblemInterface problem) :
        problem { problem }
    {
    }

    std::vector<std::shared_ptr<Node>> expand(std::shared_ptr<Node> &node) {
        std::vector<std::shared_ptr<Node>> nodes;

        for (const auto &action : problem.actions(node->state)) {
            auto next_state = problem.results(node->state, action);
            const auto cost = node->path_cost + problem.action_cost(node->state, action, next_state);

            nodes.push_back(std::make_shared<Node>(Node {
                .state = std::move(next_state),
                .parent = node,
                .action = action,
                .path_cost = cost,
                .depth = node.depth+1}));
        }

        return nodes;
    }

private:
    ProblemInterface problem;
};

}
