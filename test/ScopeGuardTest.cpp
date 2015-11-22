#include "gtest/gtest.h"
#include "ScopeGuard.h"

TEST(ScopeGuard, ActiveGuard)
{
	bool flag = false;

	{
		auto scopeGuard = BambooLib::createScopeGuard([&]() { flag = true;});

		EXPECT_EQ(flag, false);
	}

	EXPECT_EQ(flag, true);
}

TEST(ScopeGuard, DeactivatedGuard)
{
	bool flag = false;

	{
		auto scopeGuard = BambooLib::createScopeGuard([&]() { flag = true;});

		EXPECT_EQ(flag, false);

		scopeGuard.release();
	}

	EXPECT_EQ(flag, false);
}

TEST(ScopeGuard, ReleaseOnMove)
{
	int counter = 0;

	{
		EXPECT_EQ(counter, 0);

		auto scopeGuard = BambooLib::createScopeGuard([&]() { counter++; });

		// Make sure moving and destruction of rvalue object has not triggered the cleanup method
		EXPECT_EQ(counter, 0);
	}

	EXPECT_EQ(counter, 1);
}