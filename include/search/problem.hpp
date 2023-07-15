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

    struct Node {
        State state;
        std::shared_ptr<Node> parent;
        Action action;
        ActionCost path_cost;
    };

    virtual std::shared_ptr<Node> initial_node() const = 0;
    virtual State goal_state() const = 0;

    //! @todo iterator instead?
    virtual std::vector<Action> actions(const State &state) const = 0;

    virtual State results(const State &state, const Action &action) const = 0;

    virtual ActionCost action_cost(const State &state, const Action &action, const State &next_state) const = 0;
};

template <typename T>
concept IsProblem = requires(T t) {
    []<typename State, typename Action, typename ActionCost>(ProblemInterfaceTemplate<State, Action, ActionCost>&){}(t);
};

}
