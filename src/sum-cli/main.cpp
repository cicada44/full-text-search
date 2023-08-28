#include <libmath/sum.h>

#include <CLI/CLI.hpp>

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "\n\tUsage:\n\n\t\t./sum --first <firstNumber> --second "
                     "<secondNumber>\n\n";
        return 1;
    }

    CLI::App app{"Sum Calculator"};

    double first_number = 0, second_number = 0;

    app.add_option("--first", first_number, "First number")->required();
    app.add_option("--second", second_number, "Second number")->required();

    CLI11_PARSE(app, argc, argv);

    std::cout << fts::accumulate(first_number, second_number) << '\n';
}
