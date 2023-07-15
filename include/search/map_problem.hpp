#pragma once

#include "search/problem.hpp"

namespace search {

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
    static const std::string NOTHING = "";
    static const std::string LEFT = "LEFT";
    static const std::string RIGHT = "RIGHT";
    static const std::string DOWN = "DOWN";
    static const std::string UP = "UP";
}

class MapProblem : public ProblemTemplate<std::string, int> {
public:
    using ProblemType = ProblemTemplate<std::string, int>;

    MapProblem(MapProblemConfig config) :
        config { std::move(config) }
    {
        //! @todo current state representation / use doesn't hold well when there are row,col values >= 10... fix that
        if(config.rows >= 10 || config.cols >= 10) throw std::runtime_error("We can't handle that noise!");
    }

    static std::string generate_state(const MapEntry &entry) { return std::to_string(entry.row)+std::to_string(entry.col); }

    //! @todo really, we should be returning initial state & goal_state... not nodes...
    std::shared_ptr<Node> initial_node() const override { return std::make_shared<Node>(Node{.state=generate_state(config.initial), .parent=nullptr, .action=map_actions::NOTHING, .path_cost=0}); }
    std::shared_ptr<Node> goal_node() const override { return std::make_shared<Node>(Node{.state=generate_state(config.goal), .parent=nullptr, .action=map_actions::NOTHING, .path_cost=0});  }

    //! @todo iterator instead?
    std::vector<std::string> actions(const std::string &state) const override {
        size_t row = stoi(state.substr(0,1));
        size_t col = stoi(state.substr(1,1));

        std::vector<std::string> actions;
        if (row > 0) actions.push_back(map_actions::UP);
        if (row < config.rows) actions.push_back(map_actions::DOWN);
        if (col > 0) actions.push_back(map_actions::LEFT);
        if (col < config.cols) actions.push_back(map_actions::RIGHT);

        return actions;
    }

    std::string results(const std::string &state, const std::string &action) const override {
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

    int action_cost(const std::string &state, const std::string &action, const std::string &next_state) const override {
        return 1;
    }

private:
    MapProblemConfig config;
};

}
