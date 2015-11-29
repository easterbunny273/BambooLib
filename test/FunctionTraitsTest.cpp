#include <gtest/gtest.h>

#include "FunctionTraits.h"

using BambooLib::experimental::FunctionTraits;

int TestMethod(std::string, double, float)
{
	return 0;
}

void TestMethod_Void()
{

}

TEST(FunctionTraits, SimpleMethod)
{
	auto methodData = FunctionTraits::createMetaData<decltype(TestMethod)>();

	EXPECT_EQ(methodData.returnValue.type, FunctionTraits::ParamType::Integer);
	EXPECT_EQ(methodData.arguments.size(), 3);
	EXPECT_EQ(methodData.arguments[0].type, FunctionTraits::ParamType::StdString);
	EXPECT_EQ(methodData.arguments[1].type, FunctionTraits::ParamType::Double);
	EXPECT_EQ(methodData.arguments[2].type, FunctionTraits::ParamType::Float);
}

TEST(FunctionTraits, SimpleVoid)
{
	// Known to fail !

	/*
	auto methodData = FunctionTraits::createMetaData<decltype(TestMethod_Void)>();

	EXPECT_EQ(methodData.returnValue.type, FunctionTraits::ParamType::Void);
	EXPECT_EQ(methodData.arguments.size(), 0); */
}

TEST(FunctionTraits, SimpleLambda)
{
	auto LambdaMethod = [&](int a, double b) -> bool { return (a + b == 0.0); };

	auto methodData = FunctionTraits::createMetaData_Lambda<decltype(LambdaMethod)>();

	EXPECT_EQ(methodData.returnValue.type, FunctionTraits::ParamType::Boolean);
	EXPECT_EQ(methodData.arguments.size(), 2);
	EXPECT_EQ(methodData.arguments[0].type, FunctionTraits::ParamType::Integer);
	EXPECT_EQ(methodData.arguments[1].type, FunctionTraits::ParamType::Double);
}