#pragma once

#include "search/problem.hpp"

#include <memory>

namespace search {

template <typename State, typename Action, typename ActionCost>
struct NodeTemplate {
    State state;
    std::shared_ptr<NodeTemplate> parent;
    Action action;
    ActionCost path_cost;
};

template <IsProblem ProblemInterface>
using ProblemNode = NodeTemplate<typename ProblemInterface::State, typename ProblemInterface::Action, typename ProblemInterface::ActionCost>;

template <typename T>
concept IsNode = requires(T t) {
    t.state;
    t.parent;
    t.action;
    t.path_cost;
};

}
