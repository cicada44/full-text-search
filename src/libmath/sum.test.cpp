#include <libmath/sum.h>

#include <gtest/gtest.h>

TEST(math, sum) {
    double accum_result = fts::accumulate(228.0, 1337.0);
    ASSERT_EQ(accum_result, 1565.0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
