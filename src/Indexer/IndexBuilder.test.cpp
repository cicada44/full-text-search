#include <Indexer/Index.hpp>
#include <Indexer/IndexBuilder.hpp>
#include <NgramParser/NgramParser.hpp>

#include <set>
#include <string>
#include <unordered_set>
#include <utility>

#include <gtest/gtest.h>

TEST(Index, IndexBuilderNormalTexts) {
    Index::Index index_exp;

    // Test 1: Normal
    {
        Index::IndexBuilder idx_builder{{"a", "the"}, {3, 6}};
        idx_builder.add_document(1, "Matrix");
        index_exp.docs_ = {{1, "Matrix"}};
        index_exp.entries_ = {{"mat", {{1, 0}}}, {"matr", {{1, 0}}}, {"matri", {{1, 0}}}, {"matrix", {{1, 0}}}};
        ASSERT_EQ(idx_builder.index().docs_, index_exp.docs_);
        ASSERT_EQ(idx_builder.index().entries_, index_exp.entries_);
        index_exp.docs_.clear();
        index_exp.entries_.clear();
    }

    // Test 2: Normal
    {
        Index::IndexBuilder idx_builder{{"a", "the"}, {3, 6}};
        idx_builder.add_document(1, "The Matrix Revival");
        index_exp.docs_ = {{1, "The Matrix Revival"}};
        index_exp.entries_ = {{"mat", {{1, 0}}}, {"matr", {{1, 0}}}, {"matri", {{1, 0}}}, {"matrix", {{1, 0}}},
                              {"rev", {{1, 1}}}, {"revi", {{1, 1}}}, {"reviv", {{1, 1}}}, {"reviva", {{1, 1}}}};
        ASSERT_EQ(idx_builder.index().docs_, index_exp.docs_);
        ASSERT_EQ(idx_builder.index().entries_, index_exp.entries_);
        index_exp.docs_.clear();
        index_exp.entries_.clear();
    }

    // Test 3: Normal
    {
        Index::IndexBuilder idx_builder{{"a", "the"}, {3, 6}};
        idx_builder.add_document(1, "The Matrix");
        idx_builder.add_document(2, "The Matrix Revival");
        index_exp.docs_ = {{1, "The Matrix"}, {2, "The Matrix Revival"}};
        index_exp.entries_ = {{"mat", {{1, 0}, {2, 0}}},    {"matr", {{1, 0}, {2, 0}}}, {"matri", {{1, 0}, {2, 0}}},
                              {"matrix", {{1, 0}, {2, 0}}}, {"rev", {{2, 1}}},          {"revi", {{2, 1}}},
                              {"reviv", {{2, 1}}},          {"reviva", {{2, 1}}}};
        ASSERT_EQ(idx_builder.index().docs_, index_exp.docs_);
        ASSERT_EQ(idx_builder.index().entries_, index_exp.entries_);
        index_exp.docs_.clear();
        index_exp.entries_.clear();
    }

    // Test 4: Normal
    {
        Index::IndexBuilder idx_builder{{"a", "the"}, {3, 6}};
        idx_builder.add_document(1, "The Matrix");
        idx_builder.add_document(2, "The Matrix Revival");
        idx_builder.add_document(3, "The Matrix Revolutions");
        index_exp.docs_ = {{1, "The Matrix"}, {2, "The Matrix Revival"}, {3, "The Matrix Revolutions"}};
        index_exp.entries_ = {{"mat", {{1, 0}, {2, 0}, {3, 0}}},
                              {"matr", {{1, 0}, {2, 0}, {3, 0}}},
                              {"matri", {{1, 0}, {2, 0}, {3, 0}}},
                              {"matrix", {{1, 0}, {2, 0}, {3, 0}}},
                              {"rev", {{2, 1}, {3, 1}}},
                              {"revi", {{2, 1}}},
                              {"reviv", {{2, 1}}},
                              {"reviva", {{2, 1}}},
                              {"revo", {{3, 1}}},
                              {"revol", {{3, 1}}},
                              {"revolu", {{3, 1}}}};
        ASSERT_EQ(idx_builder.index().docs_, index_exp.docs_);
        ASSERT_EQ(idx_builder.index().entries_, index_exp.entries_);
        index_exp.docs_.clear();
        index_exp.entries_.clear();
    }

    // Test 4: One word repeated
    {
        Index::IndexBuilder idx_builder{{"a", "the"}, {3, 6}};
        idx_builder.add_document(1, "Matrix Matrix Matrix Matrix Matrix");
        index_exp.docs_ = {{1, "Matrix Matrix Matrix Matrix Matrix"}};
        index_exp.entries_ = {{"mat", {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}}},
                              {"matr", {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}}},
                              {"matri", {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}}},
                              {"matrix", {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}}}};
        ASSERT_EQ(idx_builder.index().docs_, index_exp.docs_);
        ASSERT_EQ(idx_builder.index().entries_, index_exp.entries_);
        index_exp.docs_.clear();
        index_exp.entries_.clear();
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
