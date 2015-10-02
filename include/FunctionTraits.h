/*
 * Author: Christian Moellinger, 2015 <ch.moellinger@gmail.com>
 * 
 * This file contains some tests to create a kind of reflection for methods, 
 * to get the number and type of arguments of a specific function.
 *
 * Problems:
 * - Cannot detect references (int& will be detected as int or templates fail to compile)
 * 
 *
 * SAMPLE CODE
 
 TTestClass testinstance;

 auto LambdaMethod = [&](int a, double b) -> int { return a + 3;};
 using Traits = function_traits<decltype(&decltype(LambdaMethod)::operator())>;


 auto methodData_Static = FunctionTraits::createMetaData<decltype(TTestClass::Test3)>();
 auto methodData = FunctionTraits::createMetaData<decltype(&(testinstance.Test2))>();
 auto methodData2 = FunctionTraits::createMetaData_Lambda<decltype(LambdaMethod)>();
 auto methodData3 = FunctionTraits::MethodData<2>(FunctionTraits::ParamType::Boolean, FunctionTraits::ArgumentVector({ FunctionTraits::ParamType::Integer, FunctionTraits::ParamType::Double}));
 std::cout << methodData.arguments.size() << std::endl;

 * END SAMPLE CODE
 *
 */

#pragma once
#ifndef __BAMBOOLIB_FUNCTIONTRAITS_H_
#define __BAMBOOLIB_FUNCTIONTRAITS_H_

#include <vector>
#include <string>

template<class F>
struct function_traits;

// function pointer
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)>
{};

template<class R, class... Args>
struct function_traits<R(Args...)>
{
	using return_type = R;

	static constexpr std::size_t arity = sizeof...(Args);

	template <std::size_t N>
	struct argument
	{
		static_assert(N < arity, "error: invalid parameter index.");
		using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	};

	typedef std::tuple<Args...> ArgTuple;
};


// member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...)> : public function_traits<R(C&, Args...)>
{};

// const member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...) const> : public function_traits<R(C&, Args...)>
{};

// member object pointer
template<class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C&)>
{};

template<class F>
struct function_traits<F&> : public function_traits<F>
{};

template<class F>
struct function_traits<F&&> : public function_traits<F>
{};

class FunctionTraits
{
public:
	enum class ParamType
	{
		Void,
		Boolean,
		Integer,
		Double,
		Float,
		StdString,
		Character
	};

	/*enum ParamModifier
	{
		None = 0,

		Pointer = 1,
		Reference = 2,
		Const = 4
	};*/



	struct Argument
	{
		ParamType type;
		//ParamModifier mod;

		bool	  isPtr, isRef, isConst;
	};

	using ArgumentVector = std::vector<Argument>;

	template <std::size_t N>
	struct MethodData
	{
	public:
		MethodData(Argument & _returnValue, ArgumentVector &v) : returnValue(_returnValue) { std::copy(v.begin(), v.end(), arguments.begin()); }
		MethodData(const MethodData &other) : returnValue(other.returnValue), arguments(other.arguments) {}

		const Argument returnValue;
		std::array<Argument, N> arguments;
	};

	template <class T> static auto createMetaData()
	{
		using Traits = function_traits<T>;

		ArgumentVector arguments;
		RecProcessArg<Traits, Traits::arity - 1>(arguments, int2type<Traits::arity - 1>());

		// The recursive walker places arguments in reverse order
		std::reverse(arguments.begin(), arguments.end());

		MethodData<Traits::arity> methodData(CreateArgument<Traits::return_type>(), arguments);

		return methodData;
	}

	template <class T> static auto createMetaData_Lambda()
	{
		using Traits = function_traits<decltype(&T::operator())>;

		ArgumentVector arguments;
		RecProcessArg_Lambda<Traits, Traits::arity - 1>(arguments, int2type<Traits::arity - 1>());

		// The recursive walker places arguments in reverse order
		std::reverse(arguments.begin(), arguments.end());

		MethodData<Traits::arity - 1> methodData(CreateArgument<Traits::return_type>(), arguments);

		return methodData;
	}

private:
	static ParamType GetParamType(std::string) { return ParamType::StdString; }
	static ParamType GetParamType(double) { return ParamType::Double; }
	static ParamType GetParamType(int) { return ParamType::Integer; }
	static ParamType GetParamType(float) { return ParamType::Float; }
	static ParamType GetParamType(bool) { return ParamType::Boolean; }
	static ParamType GetParamType(char) { return ParamType::Character; }
	static ParamType GetParamType(void) { return ParamType::Void; }

	template <class T> static Argument CreateArgument()
	{
		using T_withoutConst = std::remove_const<T>::type;
		using T_withoutPtr = std::remove_pointer<T_withoutConst>::type;
		using T_withoutRefPtr = std::remove_reference<T_withoutPtr>::type;

		Argument temp;
		temp.type = GetParamType(T_withoutRefPtr());
		temp.isPtr = std::is_pointer<T>::value;
		temp.isRef = std::is_reference<T>::value;
		temp.isConst = std::is_const<T>::value;

		/*temp.mod = ParamModifier::None;
		temp.mod = ParamModifier(temp.mod || (std::is_pointer<T>::value ? ParamModifier::Pointer : ParamModifier::None));
		temp.mod = ParamModifier(temp.mod || (std::is_reference<T>::value ? ParamModifier::Reference : ParamModifier::None));
		temp.mod = ParamModifier(temp.mod || (std::is_const<T>::value ? ParamModifier::Const : ParamModifier::None));*/

		return temp;
	}

	template <class T> static void AddArgument(ArgumentVector &argumentList) 
	{ 
		argumentList.push_back(CreateArgument<T>());
	}

	template<std::size_t> struct int2type {};

	template <class T, std::size_t N> static void RecProcessArg(ArgumentVector &arguments, int2type<N>)
	{
		AddArgument<T::argument<N>::type>(arguments);
		RecProcessArg<T>(arguments, int2type<N - 1>());
	}


	template <class T> static void RecProcessArg(ArgumentVector &arguments, int2type<0>)
	{
		AddArgument<T::argument<0>::type>(arguments);
	}

	template <class T, std::size_t N> static void RecProcessArg_Lambda(ArgumentVector &arguments, int2type<N>)
	{
		AddArgument<T::argument<N>::type>(arguments);

		RecProcessArg_Lambda<T>(arguments, int2type<N - 1>());
	}


	template <class T> void static RecProcessArg_Lambda(ArgumentVector &arguments, int2type<0>)
	{
		// do nothing, item <0> is not available for lambdas
	}
};

#endif