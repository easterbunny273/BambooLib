// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CoreSystem.h"
#include "Logger.h"

#include <Python.h>

#include <array>
#include <iostream>

#include <FunctionTraits.h>

#include <lexical_cast.h>
#include <optional.h>


bool TestMethod(const int * &iRef, double * , const std::string)
{
	return false;
}

class Test
{
public:
	Test(int i) {};
	void TestMethod() {};
};

int _tmain(int argc, _TCHAR* argv[])
{
	BambooLib::CoreSystem * pCore = BambooLib::CoreSystem::GetInstance();

	BambooLib::Logger::RegisterLogWriter(new BambooLib::Logger::ConsoleLogWriter());
	BambooLib::Logger::LogMessage(BambooLib::Logger::ERROR, "Hello du");

	auto lambdaTest = [&](const int &rTst, std::string, double &dTest) -> float { return rTst + dTest; };

	auto methodData2 = FunctionTraits::createMetaData<decltype(TestMethod)>();
	auto methodData3 = FunctionTraits::createMetaData_Lambda<decltype(lambdaTest)>();

	//Py_SetProgramName(argv[0]);
	Py_Initialize();

	auto sTest = BambooLib::lexical_cast_o<std::string>(4);
	auto iTest = BambooLib::lexical_cast<int>("9");

	auto test1 = BambooLib::optional<float>(2);
	auto test2 = BambooLib::optional<Test>();

	auto value = test1.get();

	/*auto lTest1 = BambooLib::optional<int>(4);
	auto lTest2 = BambooLib::optional<std::string>("hallo");

	Test * pTest = new Test(3);
	auto lTest3 = BambooLib::optional<int>(9);

	bool bTest1 = lTest1;
	bool bTest2 = lTest2;

	if (lTest2)
		std::cout << *lTest2 << std::endl;

	BambooLib::optional<Test> test2;
	BambooLib::optional<int> test;*/

	std::string line;

	while (std::getline(std::cin, line)) 
	{
		PyRun_SimpleString(line.c_str());
	}
	
	Py_Finalize();

	system("pause");
	return 0;
}
