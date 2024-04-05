#include <Searcher/Result.hpp>

namespace searcher {

bool score_cmp::operator()(const Result& r1, const Result& r2) const { return r1.score_ > r2.score_; }

}  // namespace searcher
