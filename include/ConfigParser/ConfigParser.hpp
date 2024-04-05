#pragma once

#include <pugixml.hpp>

#include <string>
#include <unordered_set>
#include <utility>

namespace config_parser {

using StopWordsSet = std::unordered_set<std::string>;

using NgramLenRange = std::pair<size_t, size_t>;

struct ConfigInfo {
    StopWordsSet stop_words_;
    NgramLenRange ngram_len_range_;
};

/**
 * @brief Parses a configuration file to extract settings for text analysis.
 * @param config_filename The filename of the configuration file.
 * @param text Text to be analyzed.
 * @param stop_words Set of stop words.
 * @param len_range std::pair of size_t representing the range of ngram lengths.
 */
ConfigInfo parse_config_file(const std::string &config_filename);

}  // namespace config_parser
