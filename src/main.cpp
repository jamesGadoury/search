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
    virtual shared_ptr<Node> initial() const = 0;
    virtual shared_ptr<Node> goal() const = 0;

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
vector<shared_ptr<const Node>> expand(const shared_ptr<Problem> &problem, const shared_ptr<const Node> &node) {
    vector<shared_ptr<const Node>> nodes;

    for (const string &action : problem->actions(node->state)) {
        const string next_state = problem->results(node->state, action);
        const auto cost = node->path_cost + problem->action_cost(node->state, action, next_state);

        nodes.push_back(make_shared<Node>(Node{.state=next_state, .parent=node, .action=action, .path_cost=cost}));
    }

    return nodes;
}

template<ComparesNodes EvalFunction>
optional<shared_ptr<Node>> best_first_search(const shared_ptr<Problem> problem, const EvalFunction evaluation_function) {
    shared_ptr<Node> node = problem->initial();

    priority_queue<shared_ptr<Node>> frontier(evaluation_function);

    unordered_map<string, shared_ptr<Node>> reached { { node->state, node }};

    while(!frontier.empty()) {
        node = frontier.pop();

        if(problem->goal()->state == node->state) return node;

        for (const shared_ptr<Node> &child : expand(problem, node)) {
            if(!reached.contains(child->state) || child->path_cost < reached[child->state]->path_cost) {
                reached[child->state] = child;
            }
        }
    }

    return std::nullopt;
}

int main(int argc, char *argv[]) {
    cout << "hello world" << endl;
}
