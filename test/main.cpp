#include "gtest/gtest.h"
#include "ScopeGuard.h"

TEST(A, B) { ASSERT_EQ(2, 2); }

int main(int argc, char **argv)
{
	{
		auto scopeGuard = BambooLib::createScopeGuard([&]() { std::cout << "clean up";});

		int a = 3;
		int b = a + 2;
	}
	

    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}