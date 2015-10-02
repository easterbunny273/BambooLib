#include "gtest/gtest.h"

TEST(A, B) { ASSERT_EQ(2, 1); }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}