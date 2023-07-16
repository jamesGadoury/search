#pragma once

#include "search/node.hpp"

namespace search {

enum class SolutionStatus {
    Success,
    Failed
};

template <IsNode Node>
struct Solution {
    SolutionStatus status;
    std::shared_ptr<Node> node;
    size_t expanded_count;
};
    
}
