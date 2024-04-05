#include <IndexAccessor/TextIndexAccessor.hpp>
#include <Indexer/TextIndexWriter.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace idx_accessor {

namespace {

size_t get_term_df(std::ifstream& input_file) {
    int df = 0;
    input_file >> df;
    return df;
}

DocToEntries get_term_tf(std::ifstream& input_file) {
    DocToEntries tf;
    size_t doc_id = 0;
    size_t term_entries = 0;
    size_t pos = 0;
    while (input_file >> doc_id >> term_entries) {
        tf.insert({doc_id, term_entries});
        for (size_t i = 0; i != term_entries; ++i) {
            input_file >> pos;
        }
    }
    return tf;
}

}  // namespace

TextIndexAccessor::TextIndexAccessor(std::string idx_path, config_parser::ConfigInfo config)
    : idx_path_(std::move(idx_path)), config_(std::move(config)) {
    if (!std::filesystem::exists(idx_path_)) {
        throw std::runtime_error("Error: index does not exist!");
    }
}

config_parser::ConfigInfo TextIndexAccessor::config() const { return config_; }

size_t TextIndexAccessor::total_docs() const {
    using dir_iter = std::filesystem::directory_iterator;
    const dir_iter start{idx_path_ / "index" / "docs"};
    const dir_iter end;
    return static_cast<size_t>(std::distance(start, end));
}

std::string TextIndexAccessor::load_document(const size_t doc_id) {
    using isb_iter = std::istreambuf_iterator<char>;
    std::ifstream input_file(idx_path_ / "index" / "docs" / std::to_string(doc_id));
    std::string content{isb_iter(input_file), isb_iter()};
    input_file.close();
    return content;
}

TermInfo TextIndexAccessor::get_term_info(const std::string& term) {
    std::ifstream input_doc(idx_path_ / "index" / "entries" / Index::hash_term_name(term));
    std::string term_name;
    input_doc >> term_name;
    const size_t df{get_term_df(input_doc)};
    const idx_accessor::DocToEntries tf{get_term_tf(input_doc)};
    input_doc.close();
    return {tf, df};
}

}  // namespace idx_accessor
