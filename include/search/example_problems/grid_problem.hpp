#pragma once

#include "search/problem.hpp"

#include <sstream>
    #include <iostream>

namespace search {

namespace example_problems {

/*

Grid Problem:

This is a very simple definition of a 2-dim grid problem.

It is not very optimized, and probably doesn't handle large grid representations well.

It is mainly meant as a simple example reference.

*/

struct GridEntry {
    size_t row;
    size_t col;
};

struct GridProblemConfig {
    size_t rows;
    size_t cols;
    GridEntry initial;
    GridEntry goal;
};

namespace grid_actions {
    static const std::string NOTHING = "";
    static const std::string LEFT = "LEFT";
    static const std::string RIGHT = "RIGHT";
    static const std::string DOWN = "DOWN";
    static const std::string UP = "UP";
}

std::string to_state(const GridEntry &entry) {
    std::stringstream ss;
    ss << entry.row << "," << entry.col;
    return ss.str();
}

GridEntry to_grid_entry(const std::string &state) {
    const std::string::size_type n_comma = state.find(",");

    if (std::string::npos == n_comma) {
        std::stringstream ss;
        ss << "Invalid state: " << state << " in to_grid_entry.";
        throw std::runtime_error(ss.str());
    }
    
    return {
        .row = stoul(state.substr(0, n_comma)),
        .col = stoul(state.substr(n_comma+1, state.size()))
    };
}

using GridProblemInterface = ProblemInterfaceTemplate<std::string, std::string, int>;

class GridProblem : public GridProblemInterface {
public:
    GridProblem(GridProblemConfig config) :
        config { std::move(config) }
    {
    }

    //! @todo really, we should be returning initial state & goal_state... not nodes...
    std::shared_ptr<Node> initial_node() const override {
        return std::make_shared<Node>(Node {
            .state = to_state(config.initial),
            .parent = nullptr,
            .action = grid_actions::NOTHING,
            .path_cost = 0});
    }

    std::string goal_state() const override { return to_state(config.goal); }

    std::vector<std::string> actions(const GridEntry &entry) const {
        std::vector<std::string> actions;
        if (entry.row > 0) actions.push_back(grid_actions::UP);
        if (entry.row < config.rows) actions.push_back(grid_actions::DOWN);
        if (entry.col > 0) actions.push_back(grid_actions::LEFT);
        if (entry.col < config.cols) actions.push_back(grid_actions::RIGHT);

        return actions;
    }

    //! @todo iterator instead?
    std::vector<std::string> actions(const std::string &state) const override {
        return actions(to_grid_entry(state));
    }

    std::string results(const std::string &state, const std::string &action) const override {
        GridEntry entry = to_grid_entry(state);

        if (action == grid_actions::UP) entry.row -= 1;
        else if (action == grid_actions::DOWN) entry.row += 1;
        else if (action == grid_actions::LEFT) entry.col -= 1;
        else if (action == grid_actions::RIGHT) entry.col += 1;

        return to_state(entry);
    }

    int action_cost(const std::string &state, const std::string &action, const std::string &next_state) const override {
        return 1;
    }

private:
    GridProblemConfig config;
};

}

}
