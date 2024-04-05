#pragma once

#include <iostream>

#include <set>

namespace searcher {

/**
 * @brief Contains document ID and it's score of searching.
 */
struct Result final {
    double score_;
    size_t document_id_;
};

struct score_cmp final {
    bool operator()(const Result& r1, const Result& r2) const;
};

using Results = std::multiset<Result, score_cmp>;

}  // namespace searcher
