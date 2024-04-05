#include <NgramParser/NgramParser.hpp>

#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <algorithm>

namespace ng_parser {

namespace {

void normalize_text(std::string& text) {
    text.erase(std::remove_if(text.begin(), text.end(), ispunct), text.end());
    std::transform(text.begin(), text.end(), text.begin(), tolower);
}

std::set<std::string> generate_word_ngram(const std::string& word, const NgramLenRange& ngrams_len_range) {
    std::set<std::string> single_word_ngrams;
    const size_t max_ng_len = ngrams_len_range.second;
    const size_t max_valid_ng_len = std::min(word.size(), max_ng_len);
    for (size_t ng_len = ngrams_len_range.first; ng_len <= max_valid_ng_len; ++ng_len) {
        single_word_ngrams.insert(word.substr(0, ng_len));
    }
    return single_word_ngrams;
}

}  // namespace

NgramVector parse(const std::string& s, const StopWordsSet& stop_words, const NgramLenRange& ngrams_len_range) {
    std::string text{s};
    std::string word;
    normalize_text(text);
    std::stringstream ss(text);
    NgramVector ngrams;

    while (ss >> word) {
        if (stop_words.find(word) == stop_words.end()) {  // Is it a stop word
            const std::set<std::string> single_word_ngrams{generate_word_ngram(word, ngrams_len_range)};
            if (!single_word_ngrams.empty()) {  // Check suitability
                ngrams.emplace_back(single_word_ngrams);
            }
        }
    }

    return ngrams;
}

}  // namespace ng_parser
