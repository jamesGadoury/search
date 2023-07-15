#pragma once

#include <memory>
#include <string>
#include <vector>

namespace search {

template <typename ActionT, typename ActionCostT>
class ProblemInterfaceTemplate {
public:
    using Action = ActionT;
    using ActionCost = ActionCostT;

    struct Node {
        std::string state;
        std::shared_ptr<Node> parent;
        Action action;
        ActionCost path_cost;
    };

    virtual std::shared_ptr<Node> initial_node() const = 0;
    virtual std::shared_ptr<Node> goal_node() const = 0;

    //! @todo iterator instead?
    virtual std::vector<Action> actions(const std::string &state) const = 0;

    virtual std::string results(const std::string &state, const Action &action) const = 0;

    virtual ActionCost action_cost(const std::string &state, const Action &action, const std::string &next_state) const = 0;
};

template <typename T>
concept IsProblem = requires(T t) {
    // IILE, that only binds to ProblemTemplate<...> specialisations
    // Including classes derived from them
    []<typename Action, typename ActionCost>(ProblemInterfaceTemplate<Action, ActionCost>&){}(t);
};

}
