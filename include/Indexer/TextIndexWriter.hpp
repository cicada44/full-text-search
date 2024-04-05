#pragma once

#include <Indexer/Index.hpp>
#include <Indexer/IndexWriter.hpp>

namespace Index {

class TextIndexWriter final : public IndexWriter {
public:
    /**
     * @brief Writes forward and reverse index to the path.
     * @throw std::runtime error if something went wrong.
     * @param path Path for index entry.
     * @param idx Index to writing.
     */
    void write(const fs_path& path, const Index& idx) const final;
};

/**
 * @brief Hashes term_name with SHA256 and crops first 3 bytes.
 * @param term_name Term to be cropped.
 * @return std::string Result hash with size 6.
 */
std::string hash_term_name(const std::string& term_name);

}  // namespace Index
