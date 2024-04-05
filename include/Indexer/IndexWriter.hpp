#pragma once

#include <Indexer/Index.hpp>

#include <filesystem>

namespace Index {

using fs_path = std::filesystem::path;

class IndexWriter {
public:
    virtual void write(const fs_path& path, const Index& idx) const = 0;
    virtual ~IndexWriter() = default;
};

}  // namespace Index
