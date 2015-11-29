#include <gtest/gtest.h>
#include "Variant.h"

TEST(Variant, GetInt_Direct)
{
	using bamboo::variant;
	variant test(42);

	EXPECT_EQ(test.get<int>(), 42);
}

TEST(Variant, GetInt_Ref)
{
	using bamboo::variant;
	variant test(42);

	int value;
	bool ok = test.get<int>(value);
	EXPECT_TRUE(ok);
	EXPECT_EQ(value, 42);
}

TEST(Variant, ModifyInt)
{
	using bamboo::variant;
	variant test(1337);

	test.set<int>(42);
	EXPECT_EQ(test.get<int>(), 42);
}

TEST(Variant, ModifyString)
{
	using bamboo::variant;
	variant test("hallo");

	EXPECT_EQ(test.get<std::string>(), "hallo");
	
	test.get<std::string>() = "huhu";
	
	EXPECT_EQ(test.get<std::string>(), "huhu");
}

TEST(Variant, GetWrongType_Direct)
{
	using bamboo::variant;
	variant test(1337);

	EXPECT_THROW(test.get<bool>(), std::exception);
}

TEST(Variant, GetWrongType_Ref)
{
	using bamboo::variant;
	variant test(1337);

	bool value;
	bool correctType = test.get<bool>(value);
	EXPECT_FALSE(correctType);
}

TEST(Variant, InitializeConstVector)
{
	using bamboo::variant;
	variant test(1337);

	const std::vector<variant> testVector = { variant(2), variant(42.0), variant("hallo") };

	EXPECT_EQ(testVector[0].get<int>(), 2);
	EXPECT_EQ(testVector[1].get<double>(), 42.0);
	EXPECT_EQ(testVector[2].get<std::string>(), "hallo");
}

TEST(Variant, InitializeVector)
{
	using bamboo::variant;
	variant test(1337);

	std::vector<variant> testVector = { variant(2), variant(42.0), variant("hallo") };

	EXPECT_EQ(testVector[0].get<int>(), 2);
	EXPECT_EQ(testVector[1].get<double>(), 42.0);
	EXPECT_EQ(testVector[2].get<std::string>(), "hallo");
}

TEST(Variant, TypeVector)
{
	using bamboo::variant;
	variant test(1337);

	std::vector<variant> testVector = { variant(2), variant(42.0), variant("hallo") };

	variant holdingVariant(testVector);

	EXPECT_EQ(holdingVariant.get<std::vector<variant>>(), testVector);
}