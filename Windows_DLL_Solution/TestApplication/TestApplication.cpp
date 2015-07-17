// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CoreSystem.h"
#include "Logger.h"

#include <iostream>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include <array>

template <typename T>
struct function_traits
	: public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'


template<class T> struct GetName { public: static const char * get() { return "unknown"; } };
template<> struct GetName<int> { public: static const char * get() { return "int"; } };
template<> struct GetName<double> { public: static const char * get() { return "double"; } };
template<> struct GetName<float> { public: static const char * get() { return "float"; } };
template<> struct GetName<unsigned int> { public: static const char * get() { return "unsigned int"; } };


template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
	// we specialize for pointers to member function
{
	enum { arity = sizeof...(Args) };
	// arity is the number of arguments.

	typedef ReturnType result_type;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
		// the i-th argument is equivalent to the i-th tuple element of a tuple
		// composed of those arguments.
	};

	typedef std::tuple<Args...> ArgTuple;
};


void TestMethod(double d, int i, float f1, float f2)
{

}


auto lambda = [](int i, double d, float f) { return long(i * 10); };
//auto lambda = TestMethod;
typedef function_traits<decltype(lambda)> traits;

template<int index> void do_stuff()
{
	std::cout << "test: " << index << "=" << GetName<traits::arg<index>::type>::get() << std::endl;
}

constexpr int terminate_index{ traits::arity };

void stuff_helper(std::integral_constant<int, terminate_index>)
{
}

template<int index = 0>
void stuff_helper(std::integral_constant<int, index> = std::integral_constant<int, 0>())
{
	do_stuff<index>();
	stuff_helper(std::integral_constant<int, index + 1>());
}



/*
template<class T> const char * GetName<T>() { return "unknown";  }
template <class T> const char * GetName<int>() { return "int";  }*/

int _tmain(int argc, _TCHAR* argv[])
{
	BambooLib::CoreSystem * pCore = BambooLib::CoreSystem::GetInstance();

	BambooLib::Logger::RegisterLogWriter(new BambooLib::Logger::ConsoleLogWriter());
	BambooLib::Logger::LogMessage(BambooLib::Logger::ERROR, "Hello du");

	auto lambda = [](int i, double d) { return long(i * 10); };

	typedef function_traits<decltype(lambda)> traits;

	std::cout << "INT: " << std::is_integral<traits::arg<0>::type>::value << std::endl;
	
	//for (int i = 0; i < traits::arity; i++)
	
	std::cout << "Argument " << 0 << ", type: " << GetName<traits::arg<0>::type>::get() << std::endl;
	std::cout << "Argument " << 1 << ", type: " << GetName<traits::arg<1>::type>::get() << std::endl;

	//std::initializer_list<int>{((std::cout << args), 0)...};

	/*static_for<0, traits::arity>()([&](int i)
	{
		std::cout << "Argument " << i << ", type: " << GetName<traits::arg<0>::type>::get() << std::endl;
	});*/

	stuff_helper();

	system("pause");
	return 0;
}
