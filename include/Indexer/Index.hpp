#pragma once

#include <map>
#include <string>

namespace Index {

using ForwardIndex = std::map<size_t, std::string>;

using DocToPos = std::multimap<size_t, size_t>;
using ReverseIndex = std::map<std::string, DocToPos>;

struct Index final {
    ForwardIndex docs_;
    ReverseIndex entries_;
};

}  // namespace Index
