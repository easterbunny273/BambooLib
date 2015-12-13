#include <gtest/gtest.h>
#include "Variant.h"

using BambooLib::Variant;

TEST(Variant, GetInt_Direct)
{
	Variant test(42);

	EXPECT_EQ(test.get<int>(), 42);
}

TEST(Variant, GetInt_Ref)
{
	Variant test(42);

	int value;
	bool ok = test.get<int>(value);
	EXPECT_TRUE(ok);
	EXPECT_EQ(value, 42);
}

TEST(Variant, ModifyInt)
{
	Variant test(1337);

	test.set<int>(42);
	EXPECT_EQ(test.get<int>(), 42);
}

TEST(Variant, ModifyString)
{
	Variant test("hallo");

	EXPECT_EQ(test.get<std::string>(), "hallo");
	
	test.get<std::string>() = "huhu";
	
	EXPECT_EQ(test.get<std::string>(), "huhu");
}

TEST(Variant, GetWrongType_Direct)
{
	Variant test(1337);

	EXPECT_THROW(test.get<bool>(), std::exception);
}

TEST(Variant, GetWrongType_Ref)
{
	Variant test(1337);

	bool value;
	bool correctType = test.get<bool>(value);
	EXPECT_FALSE(correctType);
}

TEST(Variant, InitializeConstVector)
{
	Variant test(1337);

	const std::vector<Variant> testVector = { Variant(2), Variant(42.0), Variant("hallo") };

	EXPECT_EQ(testVector[0].get<int>(), 2);
	EXPECT_EQ(testVector[1].get<double>(), 42.0);
	EXPECT_EQ(testVector[2].get<std::string>(), "hallo");
}

TEST(Variant, InitializeVector)
{
	Variant test(1337);

	std::vector<Variant> testVector = { Variant(2), Variant(42.0), Variant("hallo") };

	EXPECT_EQ(testVector[0].get<int>(), 2);
	EXPECT_EQ(testVector[1].get<double>(), 42.0);
	EXPECT_EQ(testVector[2].get<std::string>(), "hallo");
}

TEST(Variant, TypeVector)
{
	Variant test(1337);

	std::vector<Variant> testVector = { Variant(2), Variant(42.0), Variant("hallo") };

	Variant holdingVariant(testVector);

	EXPECT_EQ(holdingVariant.get<std::vector<Variant>>(), testVector);
}