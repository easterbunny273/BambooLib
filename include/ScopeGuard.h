#pragma once

#ifndef _BAMBOOLIB_SCOPEGUARD_H_
#define _BAMBOOLIB_SCOPEGUARD_H_

#include <functional>

namespace BambooLib
{
	template <class T>
	class ScopeGuard
	{
	public:
		ScopeGuard(const T & func) : m_func(func), m_engaged(true) {};
		ScopeGuard(const ScopeGuard<T>&& other) : m_func(other.m_func), m_engaged(other.m_engaged) {};

		~ScopeGuard() { if (m_engaged) m_func(); }
		
		ScopeGuard(const ScopeGuard<T>&) = delete;
		ScopeGuard<T>& operator=(const ScopeGuard<T> &) = delete;

		void release() { m_engaged = false; }

	private:
		T m_func;
		bool m_engaged;
	};

	template <class T> auto createScopeGuard(T & func)
	{
		return ScopeGuard<typename std::decay<T>::type>(func);
	}
}


#endif