#include <Indexer/Index.hpp>
#include <Indexer/IndexBuilder.hpp>
#include <NgramParser/NgramParser.hpp>

namespace Index {

void IndexBuilder::add_document(const size_t document_id, const std::string& text) {
    using namespace ng_parser;
    index_.docs_.insert({document_id, text});
    NgramVector ngrams(parse(text, stop_words_, lengths_));
    for (size_t ng_pos = 0, end = ngrams.size(); ng_pos != end; ++ng_pos) {
        for (const auto& term : ngrams[ng_pos]) {
            index_.entries_[term].insert({document_id, ng_pos});
        }
    }
}

Index IndexBuilder::index() const { return index_; }

}  // namespace Index
