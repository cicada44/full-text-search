#pragma once

#include <IndexAccessor/IndexAccessor.hpp>
#include <Indexer/IndexWriter.hpp>

namespace idx_accessor {

class TextIndexAccessor final : public IndexAccessor {
public:
    TextIndexAccessor(std::string idx_path, config_parser::ConfigInfo config);

    size_t total_docs() const final;

    std::string load_document(size_t doc_id) final;

    TermInfo get_term_info(const std::string& term) final;

    config_parser::ConfigInfo config() const;

    ~TextIndexAccessor() final = default;

private:
    Index::fs_path idx_path_;
    config_parser::ConfigInfo config_;
};

}  // namespace idx_accessor
