#pragma once

#ifndef __BAMBOOLIB_LEXICALCAST_H_
#define __BAMBOOLIB_LEXICALCAST_H_

#include <string>
#include <sstream>
#include <exception>

#include "optional.h"

namespace BambooLib
{
	class bad_lexical_cast : public std::exception
	{
	public:
		bad_lexical_cast() : std::exception() {};
		bad_lexical_cast(const char * msg) : std::exception(msg) {};
	};

	template <class D, class S> D lexical_cast(S sourceVal)
	{
		D result;

		std::stringstream bufferStream;

		bufferStream << sourceVal;
		bufferStream >> result;

		if (bufferStream.fail() || bufferStream.eof()==false)
			throw bad_lexical_cast();

		return result;
	};

	template<class S> std::string lexical_cast(S sourceVal)
	{
		std::stringstream bufferStream;
		
		bufferStream << sourceVal;

		if (bufferStream.fail())
			throw bad_lexical_cast();

		return bufferStream.str();
	};

	template <class D, class S> auto lexical_cast_o(S sourceVal)
	{
		D buffer;
		BambooLib::optional<D> result;

		std::stringstream bufferStream;
		bufferStream << sourceVal;
		bufferStream >> buffer;

		if (!bufferStream.fail() && bufferStream.eof())
			result.set(buffer);

		return result;
	};

	template<class S> auto lexical_cast_o(S sourceVal)
	{
		BambooLib::optional<std::string> result;

		std::stringstream bufferStream;
		bufferStream << sourceVal;

		if (!bufferStream.fail())
			result.set(bufferStream.str());

		return result;
	};
};



#endif