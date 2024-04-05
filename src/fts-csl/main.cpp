#include <ConfigParser/ConfigParser.hpp>
#include <Filter/Filter.hpp>
#include <IndexAccessor/TextIndexAccessor.hpp>
#include <Indexer/IndexBuilder.hpp>
#include <Indexer/TextIndexWriter.hpp>
#include <NgramParser/NgramParser.hpp>
#include <Searcher/Result.hpp>
#include <Searcher/Searcher.hpp>

#include <CLI/CLI.hpp>
#include <csv.hpp>
#include <replxx.hxx>

#include <string>

#include <iostream>

namespace {

void compose_index(const std::string &csv_path, const std::string &idx_path_str,
                   const config_parser::ConfigInfo &config_info) {
    std::string text;
    Index::IndexBuilder idx_builder{config_info.stop_words_, config_info.ngram_len_range_};
    csv::CSVReader csv_file = csv::CSVReader(csv_path);
    std::string id;
    for (auto &row : csv_file) {
        id = row["bookID"];
        id = id.substr(id.find_first_of(' ') + 1);
        text = row["title"];
        text = text.substr(text.find_first_of(' ') + 1);
        idx_builder.add_document(std::stol(id), text);
    }
    const Index::Index idx{idx_builder.index()};
    const Index::fs_path idx_path(idx_path_str);
    const Index::TextIndexWriter idx_writer;
    try {
        idx_writer.write(idx_path, idx);
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
    std::cout << std::endl;
}

void search_interactive(const std::string &idx_path_str, const config_parser::ConfigInfo &config_info) {
    idx_accessor::TextIndexAccessor idx_accessor{idx_path_str, config_info};
    searcher::Results results;
    std::string query;
    const std::string prompt;

    using namespace replxx;
    Replxx rx;
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::UP), "hint_previous");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::DOWN), "hint_next");

    while (true) {
        query = rx.input("> ");
        if (query.compare(0, 6, ".clear") == 0) {
            rx.clear_screen();
            continue;
        }
        if (query.compare(0, 5, ".quit") == 0 || query.compare(0, 5, ".exit") == 0) {
            rx.history_add(query);
            return;
        }

        results = searcher::search(query, idx_accessor);
        rx.history_add(query);

        if (results.empty()) {
            std::cout << "No results" << std::endl;
        }

        filter::filter(results);

        for (const auto &result : results) {
            std::cout << result.score_ << '\t' << result.document_id_ << '\t'
                      << idx_accessor.load_document(result.document_id_);
        }
        std::cout << '\n';
    }
}

}  // namespace

int main(int argc, char *argv[]) {
    CLI::App app{"Full-text-search application"};
    std::string mode;

    std::string config_filename{"default.xml"};
    std::string csv_path;
    std::string idx_path_str;
    std::string query;

    app.add_option("--config", config_filename, "Config filename");
    app.add_option("--query", query, "Query to search");
    app.add_option("--index", idx_path_str, "Path to index to write");
    app.add_option("--csv", csv_path, "Path to books csv file");
    app.add_option("index", mode, "Indexing mode");
    app.add_option("search", mode, "Searching mode");

    try {
        CLI11_PARSE(app, argc, argv);
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }
    if (app.count("--help") > 0) {
        return 0;
    }

    config_parser::ConfigInfo config_info;
    try {
        config_info = config_parser::parse_config_file(config_filename);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what();
        return 1;
    }

    if (mode == "index") {
        if (csv_path.empty()) {
            std::cerr << "Error: --csv is required\n";
            return -1;
        }
        if (idx_path_str.empty()) {
            std::cerr << "Error: --index is required\n";
            return -1;
        }
        compose_index(csv_path, idx_path_str, config_info);
    } else if (mode == "search") {
        if (idx_path_str.empty()) {
            std::cerr << "Error: --index is required\n";
            return -1;
        }

        if (query.empty()) {
            search_interactive(idx_path_str, config_info);
        } else {
            idx_accessor::TextIndexAccessor accessor{idx_path_str, config_info};
            searcher::Results results = searcher::search(query, accessor);
            filter::filter(results);
            for (const auto &result : results) {
                std::cout << result.score_ << '\t' << result.document_id_ << '\t'
                          << accessor.load_document(result.document_id_);
            }
            std::cout << '\n';
        }
    } else {
        std::cout << app.help();
    }
}
