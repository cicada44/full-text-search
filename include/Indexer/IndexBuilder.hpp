#pragma once

#include <Indexer/Index.hpp>
#include <NgramParser/NgramParser.hpp>

namespace Index {

class IndexBuilder final {
public:
    IndexBuilder(ng_parser::StopWordsSet stop_words, ng_parser::NgramLenRange lengts)
        : stop_words_(std::move(stop_words)), lengths_(std::move(lengts)) {}

    /**
     * @brief Adds new document with document_id and text to index.
     * @param document_id Id of document.
     * @param text Text of document.
     */
    void add_document(size_t document_id, const std::string& text);

    /**
     * @brief Returns index.
     * @return Index
     */
    Index index() const;

private:
    Index index_;

    ng_parser::StopWordsSet stop_words_;
    ng_parser::NgramLenRange lengths_;
};

}  // namespace Index
