#include <picosha2.h>

#include <ConfigParser/ConfigParser.hpp>
#include <IndexAccessor/TextIndexAccessor.hpp>
#include <Indexer/TextIndexWriter.hpp>
#include <NgramParser/NgramParser.hpp>
#include <Searcher/Searcher.hpp>

#include <cmath>

#include <functional>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace searcher {

using namespace idx_accessor;

namespace {

using TermToInfo = std::map<std::string, TermInfo>;

using TermToFriquency = std::map<std::string, size_t>;

TermToInfo generate_term_to_info(const ng_parser::NgramVector& ngrams, TextIndexAccessor& idx_accessor) {
    TermToInfo term_infos;
    for (const auto& single_word_ngrams : ngrams) {
        for (const auto& term : single_word_ngrams) {
            term_infos.insert({term, idx_accessor.get_term_info(term)});
        }
    }
    return term_infos;
}

DocToTermInfo generate_doc_to_info(const TermToInfo& term_infos) {
    DocToTermInfo docs_to_info;
    for (const auto& [term, info] : term_infos) {
        for (const auto& [doc, entries] : info.tf_) {
            docs_to_info[doc].insert({term, entries});
        }
    }
    return docs_to_info;
}

double calc_score(const TermToInfo& term_infos, const TermToFriquency& info, const size_t number_docs) {
    double score = 0.0;
    for (const auto& [term, tf] : info) {
        if (term_infos.find(term) != term_infos.end()) {
            score += (static_cast<double>(tf) *
                      std::log(static_cast<double>(number_docs) / static_cast<double>(term_infos.at(term).df_)));
        }
    }
    return score;
}

Results compose_scores(TextIndexAccessor& idx_accessor, const TermToInfo& term_infos,
                       const DocToTermInfo& docs_to_info) {
    Results results;
    const size_t number_docs{idx_accessor.total_docs()};
    for (const auto& [doc, info] : docs_to_info) {
        results.insert({calc_score(term_infos, info, number_docs), doc});
    }
    return results;
}

}  // namespace

Results search(const std::string& query, TextIndexAccessor& idx_accessor) {
    using namespace ng_parser;
    using namespace config_parser;
    const ConfigInfo config{idx_accessor.config()};
    const NgramVector ngrams{parse(query, config.stop_words_, config.ngram_len_range_)};
    const TermToInfo term_infos{generate_term_to_info(ngrams, idx_accessor)};
    const DocToTermInfo docs_to_info{generate_doc_to_info(term_infos)};
    return compose_scores(idx_accessor, term_infos, docs_to_info);
}

}  // namespace searcher
