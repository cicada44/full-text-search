#pragma once

#include <IndexAccessor/TextIndexAccessor.hpp>
#include <Searcher/Result.hpp>

#include <functional>

#include <map>
#include <set>
#include <string>

namespace searcher {

using DocToTermInfo = std::map<size_t, std::map<std::string, size_t>>;

/**
 * @brief Composes results of searching query.
 * @param query Text query to searching.
 * @param idx_accessor TextIndexAccessor object for access to term information.
 * @return Results Results object with scores of documents.
 */
Results search(const std::string& query, idx_accessor::TextIndexAccessor& idx_accessor);

}  // namespace searcher
