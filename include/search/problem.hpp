#pragma once

#include <memory>
#include <string>
#include <vector>

namespace search {

template <typename StateT, typename ActionT, typename ActionCostT>
class ProblemInterfaceTemplate {
public:
    using State = StateT;
    using Action = ActionT;
    using ActionCost = ActionCostT;

    virtual ~ProblemInterfaceTemplate() = default;

    virtual State initial_state() const = 0;
    virtual State goal_state() const = 0;

    virtual std::vector<Action> actions(const State &state) const = 0;

    virtual State result(const State &state, const Action &action) const = 0;

    virtual ActionCost action_cost(const State &state, const Action &action, const State &next_state) const = 0;
};

template <typename T>
concept IsProblem = requires(T t) {
    []<typename State, typename Action, typename ActionCost>(ProblemInterfaceTemplate<State, Action, ActionCost>&){}(t);
};

}
