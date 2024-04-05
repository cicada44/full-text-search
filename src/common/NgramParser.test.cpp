#include <NgramParser/NgramParser.hpp>

#include <set>
#include <string>
#include <unordered_set>
#include <utility>

#include <gtest/gtest.h>

TEST(NgramParser, ParseFunction) {
    std::string text;
    const ng_parser::StopWordsSet stop_words{"a", "the", "with"};
    ng_parser::NgramLenRange ngrams_len_range;
    ng_parser::NgramVector ngrams;

    // Test 1: Normal
    {
        text = "Abracadabra! The magic spell worked with a flourish.";
        ngrams_len_range = {3, 5};
        const ng_parser::NgramVector expected_ngrams{{"abr", "abra", "abrac"},
                                                     {"mag", "magi", "magic"},
                                                     {"spe", "spel", "spell"},
                                                     {"wor", "work", "worke"},
                                                     {"flo", "flou", "flour"}};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }

    // Test 2: Normal
    {
        text = "The fox with the lazy smile outwitted the quick dog.";
        ngrams_len_range = {2, 4};
        const ng_parser::NgramVector expected_ngrams{{"fo", "fox"},         {"la", "laz", "lazy"},
                                                     {"sm", "smi", "smil"}, {"ou", "out", "outw"},
                                                     {"qu", "qui", "quic"}, {"do", "dog"}};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }

    // Test 3: Normal
    {
        text = "A bee buzzed by, creating a cheerful melody...";
        ngrams_len_range = {4, 6};
        const ng_parser::NgramVector expected_ngrams{{"buzz", "buzze", "buzzed"},
                                                     {"crea", "creat", "creati"},
                                                     {"chee", "cheer", "cheerf"},
                                                     {"melo", "melod", "melody"}};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }

    // Test 4: Empty Text
    {
        text = "";
        ngrams_len_range = {2, 4};
        const ng_parser::NgramVector expected_ngrams{};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }

    // Test 5: Special Characters
    {
        text = "The @#^%! dog with $100!";
        ngrams_len_range = {2, 3};
        const ng_parser::NgramVector expected_ngrams{{"do", "dog"}, {"10", "100"}};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }

    // Test 6: Long Words
    {
        text = "Supercalifragilisticexpialidocious";
        ngrams_len_range = {5, 10};
        const ng_parser::NgramVector expected_ngrams{
            {"super", "superc", "superca", "supercal", "supercali", "supercalif"}};
        ngrams = ng_parser::parse(text, stop_words, ngrams_len_range);
        ASSERT_EQ(ngrams, expected_ngrams);
        ngrams.clear();
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
