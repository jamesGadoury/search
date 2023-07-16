#pragma once

#include "search/node.hpp"

namespace search {

enum class ProblemStatus {
    Solved,
    Unsolved
};

template <typename Node>
struct Result {
    ProblemStatus status;
    std::shared_ptr<Node> node;
    size_t expanded_count;
};
    
}
