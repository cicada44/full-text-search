#include <Indexer/IndexWriter.hpp>
#include <Indexer/TextIndexWriter.hpp>

#include <picosha2.h>

namespace Index {

namespace {

void create_required_directories(const fs_path& path) {
    using namespace std::filesystem;
    create_directories(path / "index" / "docs");
    create_directories(path / "index" / "entries");
    if (!std::filesystem::exists(path / "index")) {
        throw std::runtime_error("Can't find required directories!");
    }
}

void write_forward_index(const fs_path& path, const ForwardIndex& idx) {
    for (const auto& [doc_id, doc_text] : idx) {
        std::ofstream output_file(path / "index" / "docs" / std::to_string(doc_id));
        if (!output_file.is_open()) {
            throw std::runtime_error("Can't create forward-index file!");
        }
        output_file << doc_text << '\n';
        output_file.close();
    }
}

std::string generate_term_info(const std::string& term_name, const DocToPos& doc_to_pos) {
    const std::map<size_t, size_t> unique_doc_to_pos(doc_to_pos.begin(), doc_to_pos.end());
    std::string term_info;
    term_info.append(term_name + ' ');
    term_info.append(std::to_string(unique_doc_to_pos.size()) + ' ');

    for (const auto& [doc, pos] : unique_doc_to_pos) {
        term_info.append(std::to_string(doc) + ' ');
        term_info.append(std::to_string(doc_to_pos.count(doc)) + ' ');
        for (auto [beg_entries, end_entries] = doc_to_pos.equal_range(doc); beg_entries != end_entries; ++beg_entries) {
            term_info.append(std::to_string(beg_entries->second) + ' ');
        }
    }
    term_info.append("\n");

    return term_info;
}

void write_reverse_index(const fs_path& path, const ReverseIndex& idx) {
    for (const auto& [term_name, doc_to_pos] : idx) {
        std::ofstream output_file(path / "index" / "entries" / hash_term_name(term_name));
        if (!output_file.is_open()) {
            throw std::runtime_error("Can't create reverse-index file!");
        }
        const std::string term_info = generate_term_info(term_name, doc_to_pos);
        output_file << term_info;
        output_file.close();
    }
}

}  // namespace

std::string hash_term_name(const std::string& term_name) {
    return picosha2::hash256_hex_string(term_name).substr(0, 6);
}

void TextIndexWriter::write(const fs_path& path, const Index& idx) const {
    try {
        create_required_directories(path);
        write_forward_index(path, idx.docs_);
        write_reverse_index(path, idx.entries_);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error while writing index: " + std::string(e.what()));
    }
}

}  // namespace Index
