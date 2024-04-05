#include <ConfigParser/ConfigParser.hpp>

#include <pugixml.hpp>

#include <string>
#include <utility>

#include <iostream>

namespace config_parser {

namespace {

bool open_and_validate_file(pugi::xml_document &doc, const std::string &filename) {
    const pugi::xml_parse_result result = doc.load_file(filename.c_str());
    return (result.status == pugi::xml_parse_status::status_ok);
}

StopWordsSet extract_stop_words(const pugi::xml_node &fts_node) {
    StopWordsSet stop_words;
    const pugi::xml_node stop_word_node{fts_node.child("parser").child("stop_words")};
    for (const pugi::xml_node &word_node : stop_word_node.children("word")) {
        stop_words.insert(word_node.child_value());
    }
    return stop_words;
}

NgramLenRange extract_ngram_lengths(const pugi::xml_node &fts_node) {
    const pugi::xml_node parser_node = fts_node.child("parser");
    return {parser_node.attribute("ngram_min_length").as_int(), parser_node.attribute("ngram_max_length").as_int()};
}

}  // namespace

ConfigInfo parse_config_file(const std::string &config_filename) {
    pugi::xml_document doc;

    if (!open_and_validate_file(doc, config_filename)) {
        throw std::runtime_error("Error while parsing file!\n");
    }

    const pugi::xml_node fts_node = doc.child("fts");

    return {extract_stop_words(fts_node), extract_ngram_lengths(fts_node)};
}

}  // namespace config_parser
