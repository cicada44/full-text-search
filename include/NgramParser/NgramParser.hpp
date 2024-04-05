#pragma once

#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <algorithm>

namespace ng_parser {

using NgramVector = std::vector<std::set<std::string>>;

using StopWordsSet = std::unordered_set<std::string>;

using NgramLenRange = std::pair<size_t, size_t>;

/**
 * @brief Parses input text, extracting ngrams while ignoring stop words.
 * @param input_text The text to parse.
 * @param stop_words A set of stop words to be ignored in the text.
 * @param ngrams_len_range A pair of size_t representing the range of ngram
 * lengths.
 * @return NgramVector vector of resulted ngrams.
 */
NgramVector parse(const std::string& s, const StopWordsSet& stop_words, const NgramLenRange& ngrams_len_range);

}  // namespace ng_parser
