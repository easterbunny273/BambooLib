#include <gtest/gtest.h>

#include "lexical_cast.h"
#include "optional.h"

TEST(LexicalCast, StringToInt)
{
	std::string test1("42");
	EXPECT_EQ(BambooLib::lexical_cast<int>(test1), 42);
}

TEST(LexicalCast, StringToDouble)
{
	std::string test1("42.1337");
	EXPECT_DOUBLE_EQ(BambooLib::lexical_cast<double>(test1), 42.1337);
}

TEST(LexicalCast, StringToFloat)
{
	std::string test1("42.1337");
	EXPECT_FLOAT_EQ(BambooLib::lexical_cast<float>(test1), 42.1337f);
}

TEST(LexicalCast, IntToString)
{
	EXPECT_EQ(BambooLib::lexical_cast<std::string>(42), "42");
}

TEST(LexicalCast, FloatToString)
{
	EXPECT_EQ(BambooLib::lexical_cast<std::string>(42.1337f), "42.1337");
}

TEST(LexicalCast, DoubleToString)
{
	EXPECT_EQ(BambooLib::lexical_cast<std::string>(42.1337), "42.1337");
}

TEST(LexicalCast, InvalidStringThrowsError)
{
	std::string test1("42.1337 188");

	EXPECT_THROW(BambooLib::lexical_cast<float>(test1), BambooLib::bad_lexical_cast);
}

TEST(LexicalCast, EmnptyStringThrowsError)
{
	std::string test1("");

	EXPECT_THROW(BambooLib::lexical_cast<float>(test1), BambooLib::bad_lexical_cast);
}


TEST(LexicalCast_o, InvalidStringReturnsEmptyOptional)
{
	std::string test1("42.1337 188");

	auto optionalObject = BambooLib::lexical_cast_o<float>(test1);

	EXPECT_FALSE(optionalObject.is_set());
}

TEST(LexicalCast_o, ValidStringReturnsSetOptional)
{
	std::string test1("42.1337");

	auto optionalObject = BambooLib::lexical_cast_o<float>(test1);

	EXPECT_TRUE(optionalObject.is_set());
}

TEST(LexicalCast_o, DoubleToString)
{
	auto optionalObject = BambooLib::lexical_cast_o<std::string>(42.1337);

	EXPECT_EQ(optionalObject.get(), "42.1337");
}

TEST(LexicalCast_o, FloatToString)
{
	auto optionalObject = BambooLib::lexical_cast_o<std::string>(42.1337f);

	EXPECT_EQ(optionalObject.get(), "42.1337");
}

TEST(LexicalCast_o, StringToFloat)
{
	auto optionalObject = BambooLib::lexical_cast_o<float>("42.27");

	EXPECT_FLOAT_EQ(optionalObject.get(), 42.27f);
}

TEST(LexicalCast_o, StringToDouble)
{
	auto optionalObject = BambooLib::lexical_cast_o<double>("42.27");

	EXPECT_DOUBLE_EQ(optionalObject.get(), 42.27);
}

TEST(LexicalCast_o, StringToInt)
{
	auto optionalObject = BambooLib::lexical_cast_o<int>("42");

	EXPECT_EQ(optionalObject.get(), 42);
}

TEST(LexicalCast_o, EmptyStringToInt)
{
	auto optionalObject = BambooLib::lexical_cast_o<int>("");

	EXPECT_FALSE(optionalObject.is_set());
}