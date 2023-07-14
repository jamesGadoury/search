#include <iostream>
#include <optional>
#include <functional>
#include <queue>
#include <concepts>
#include <memory>

using namespace std;

struct Node {
    string state;
    shared_ptr<const Node> parent;
    string action;
    int path_cost;
};

class Problem {
public:
    virtual shared_ptr<Node> initial_node() const = 0;
    virtual shared_ptr<Node> goal_node() const = 0;

    //! @todo iterator instead?
    virtual vector<string> actions(const string &state) const = 0;

    virtual string results(const string &state, const string &action) const = 0;

    virtual int action_cost(const string &state, const string &action, const string &next_state) const = 0;

};

template <typename T>
concept ComparesNodes = requires(T t) {
    { t(make_shared<Node>(), make_shared<Node>()) } -> std::same_as<bool>;
};

// Temporary proto code -> state is encoded as a string...

//! @todo make into generator iterator...
vector<shared_ptr<Node>> expand(const shared_ptr<Problem> &problem, const shared_ptr<const Node> &node) {
    vector<shared_ptr<Node>> nodes;

    for (const string &action : problem->actions(node->state)) {
        const string next_state = problem->results(node->state, action);
        const auto cost = node->path_cost + problem->action_cost(node->state, action, next_state);

        nodes.push_back(make_shared<Node>(Node{.state=next_state, .parent=node, .action=action, .path_cost=cost}));
    }

    return nodes;
}

template<typename EvalFunction>
optional<shared_ptr<Node>> best_first_search(const shared_ptr<Problem> problem, const EvalFunction evaluation_function) {
    shared_ptr<Node> node = problem->initial_node();

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, EvalFunction> frontier(evaluation_function);
    frontier.push(node);

    unordered_map<string, shared_ptr<Node>> reached { { node->state, node }};

    while(!frontier.empty()) {
        node = frontier.top();
        frontier.pop();

        if(problem->goal_node()->state == node->state) return node;

        for (const shared_ptr<Node> &child : expand(problem, node)) {
            if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                reached[child->state] = child;
                frontier.push(child);
            }
        }
    }

    return std::nullopt;
}

struct MapEntry {
    size_t row;
    size_t col;
};

struct MapProblemConfig {
    size_t rows;
    size_t cols;
    MapEntry initial;
    MapEntry goal;
};

namespace map_actions {
    static const string NOTHING = "";
    static const string LEFT = "LEFT";
    static const string RIGHT = "RIGHT";
    static const string DOWN = "DOWN";
    static const string UP = "UP";
}

class MapProblem : public Problem {
public:
    MapProblem(MapProblemConfig config) :
        config { move(config) }
    {
        //! @todo current state representation / use doesn't hold well when there are row,col values >= 10... fix that
        if(config.rows >= 10 || config.cols >= 10) throw runtime_error("We can't handle that noise!");
    }

    static string generate_state(const MapEntry &entry) { return to_string(entry.row)+to_string(entry.col); }

    //! @todo really, we should be returning initial state & goal_state... not nodes...
    shared_ptr<Node> initial_node() const override { return make_shared<Node>(Node{.state=generate_state(config.initial), .parent=nullptr, .action=map_actions::NOTHING, .path_cost=0}); }
    shared_ptr<Node> goal_node() const override { return make_shared<Node>(Node{.state=generate_state(config.goal), .parent=nullptr, .action=map_actions::NOTHING, .path_cost=0});  }

    //! @todo iterator instead?
    vector<string> actions(const string &state) const override {
        size_t row = stoi(state.substr(0,1));
        size_t col = stoi(state.substr(1,1));

        vector<string> actions;
        if (row > 0) actions.push_back(map_actions::UP);
        if (row < config.rows) actions.push_back(map_actions::DOWN);
        if (col > 0) actions.push_back(map_actions::LEFT);
        if (col < config.cols) actions.push_back(map_actions::RIGHT);

        return actions;
    }

    string results(const string &state, const string &action) const override {
        size_t row = stoi(state.substr(0,1));
        size_t col = stoi(state.substr(1,1));

        if (action == map_actions::UP) {
            row -= 1;
        } else if (action == map_actions::DOWN) {
            row += 1;
        } else if (action == map_actions::LEFT) {
            col -= 1;
        } else if (action == map_actions::RIGHT) {
            col += 1;
        }

        return generate_state(MapEntry{.row=row, .col=col});
    }

    int action_cost(const string &state, const string &action, const string &next_state) const override {
        return 1;
    }

private:
    MapProblemConfig config;
};

int main(int argc, char *argv[]) {
    const shared_ptr<Problem> problem = make_shared<MapProblem>(MapProblemConfig{.rows=9,.cols=9,.initial=MapEntry{.row=1,.col=1},.goal=MapEntry{.row=7,.col=5}});

    auto cmp = [](shared_ptr<Node> a, shared_ptr<Node> b) {return a->path_cost < b->path_cost; };
    auto found_solution = best_first_search(problem, cmp);

    if (!found_solution.has_value()) { 
        cout << "Failed to find solution." << endl;
        return -1;
    } 

    cout << "Found state: " << found_solution.value()->state << endl;
    cout << "Cost: " << found_solution.value()->path_cost << endl;

}
