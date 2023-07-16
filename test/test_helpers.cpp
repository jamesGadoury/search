#include "doctest.h"

#include <search/helpers.hpp>

#include <functional>

using namespace std;
using namespace search;

using TestNode = NodeTemplate<int, int, int>;

auto generate_search_tree_leaf() {
    auto child = make_shared<TestNode>(TestNode {
        .state = 2,
        .parent = nullptr,
        .action = 1,
        .path_cost = 2
    });

    auto head = child;

    head->parent = make_shared<TestNode>(TestNode {
        .state = 1,
        .parent = nullptr,
        .action = 1,
        .path_cost = 1
    });

    head = head-> parent;

    head->parent = make_shared<TestNode>(TestNode {
        .state = 0,
        .parent = nullptr,
        .action = 0,
        .path_cost = 0
    });

    return child;
}

TEST_CASE("Testing depth") {
    CHECK(depth(*(generate_search_tree_leaf())) == 2);
}

TEST_CASE("Testing actions_to_node") {
    const list<int> expected_actions = invoke([]() {
        list<int> expected_actions;
        expected_actions.push_back(1);
        expected_actions.push_back(1);
        return expected_actions;
    });

    CHECK(actions_to_node(*(generate_search_tree_leaf())) == expected_actions);
}

TEST_CASE("Testing has_cycle") {
    auto node = generate_search_tree_leaf();

    CHECK(!has_cycle(*node));

    // Add node that would take action back to a prior state
    auto next = make_shared<TestNode>(TestNode {
        .state = 1,
        .parent = node,
        .action = -1,
        .path_cost = 3
    });

    CHECK(has_cycle(*next));

    // Now try to add a bunch of nodes to test the 
    // optional evaluation_depth param.
    for (int state = 2; state < 5; ++state) {
        next = make_shared<TestNode>(TestNode {
            .state = state,
            .parent = next,
            .action = 1,
            .path_cost = next->path_cost + 1
        });
    }

    // Confirm has_cycle still is true with
    // unspecified evaluation_depth param
    CHECK(has_cycle(*next));

    // Confirm has_cycle still is true with
    // evaluation_depth param that is just large enough
    CHECK(has_cycle(*next, 3));

    // Confirm has_cycle is now false if
    // evaluation_depth param that is not large enough.
    // While maybe unideal from a user perspective,
    // it does show the function is acting "as expected".
    CHECK(!has_cycle(*next, 2));
}
