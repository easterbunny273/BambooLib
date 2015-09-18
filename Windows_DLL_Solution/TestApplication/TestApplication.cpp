// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CoreSystem.h"
#include "Logger.h"

#include <Python.h>

#include <array>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	BambooLib::CoreSystem * pCore = BambooLib::CoreSystem::GetInstance();

	BambooLib::Logger::RegisterLogWriter(new BambooLib::Logger::ConsoleLogWriter());
	BambooLib::Logger::LogMessage(BambooLib::Logger::ERROR, "Hello du");

	//Py_SetProgramName(argv[0]);
	Py_Initialize();

	std::string line;

	while (std::getline(std::cin, line)) 
	{
		PyRun_SimpleString(line.c_str());
	}
	
	Py_Finalize();

	system("pause");
	return 0;
}
