#pragma once

#include "search/problem.hpp"

#include <memory>

namespace search {

template <IsProblem ProblemInterface>
struct NodeTemplate {
    ProblemInterface::State state;
    std::shared_ptr<NodeTemplate> parent;
    ProblemInterface::Action action;
    ProblemInterface::ActionCost path_cost;
};

template <typename T>
concept IsNode = requires(T t) {
    []<IsProblem Problem>(NodeTemplate<Problem>&){}(t);
};

}
