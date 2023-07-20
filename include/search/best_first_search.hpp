#pragma once

#include "search/helpers.hpp"
#include "search/result.hpp"

#include <optional>
#include <queue>
#include <unordered_map>
#include <functional>

namespace search {

template<IsProblem ProblemInterface>
using EvalFunction = std::function<bool(const std::shared_ptr<ProblemNode<ProblemInterface>> &, const std::shared_ptr<ProblemNode<ProblemInterface>> &)>;

template<IsProblem ProblemInterface>
Result<ProblemNode<ProblemInterface>> best_first_search(
    const ProblemInterface &problem,
    const EvalFunction<ProblemInterface> evaluation
) {
    using Node = ProblemNode<ProblemInterface>;

    std::shared_ptr<Node> node = std::make_shared<Node>(Node {
        .state = problem.initial_state(),
        .parent = nullptr,
        .action = {},
        .path_cost = 0});

    const EvalFunction<ProblemInterface> inverse_evaluation = [evaluation](const auto &a, const auto &b) { return evaluation(b, a); };
    
    // This may seem counter-intuitive, please read the section of the Compare param here:
    // https://en.cppreference.com/w/cpp/container/priority_queue
    // Essentially, we flip the input evaluation_function result so that the items we
    // want "first" come last in the queue. This makes it so the consumer of the function
    // can provide an evaluation_function that makes more sense on their end.
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, EvalFunction<ProblemInterface>> frontier(inverse_evaluation);

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
