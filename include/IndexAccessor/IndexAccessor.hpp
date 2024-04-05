#pragma once

#include <ConfigParser/ConfigParser.hpp>

#include <map>

namespace idx_accessor {

using DocToEntries = std::map<size_t, size_t>;

struct TermInfo final {
    DocToEntries tf_;
    size_t df_;
};

class IndexAccessor {
public:
    /**
     * @brief Returs ConfigInfo object for parser working.
     * @return config_parser::ConfigInfo Config for parser.
     */
    virtual config_parser::ConfigInfo config() const = 0;

    /**
     * @brief Returns the TermInfo object for term.
     * @param term Term for extracting info.
     * @return TermInfo Info of term.
     */
    virtual TermInfo get_term_info(const std::string& term) = 0;

    /**
     * @brief Returns indexed documents number.
     * @return size_t Nubmer of docs.
     */
    virtual size_t total_docs() const = 0;

    /**
     * @brief Reads document with forward index in it.
     * @param doc_id ID of loading document.
     * @return std::string Content of document.
     */
    virtual std::string load_document(size_t doc_id) = 0;

    virtual ~IndexAccessor() = default;
};

}  // namespace idx_accessor
