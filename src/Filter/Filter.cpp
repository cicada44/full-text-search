#include <Searcher/Result.hpp>

#include <Filter/Filter.hpp>

#include <algorithm>

namespace {

void filter_for_score(searcher::Results& results) {
    double median_score = 0.0;
    for (const auto& result : results) {
        median_score += result.score_;
    }
    median_score /= static_cast<double>(results.size());
    for (auto it = results.begin(); it != results.end();) {
        if (it->score_ <=
            median_score - std::min_element(results.begin(), results.end(), searcher::score_cmp())->score_) {
            it = results.erase(it);
        } else {
            ++it;
        }
    }
}

}  // namespace

namespace filter {

void filter(searcher::Results& results) { filter_for_score(results); }

}  // namespace filter
