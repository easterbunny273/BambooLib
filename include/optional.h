// cmoellinger, 09/2015

#pragma once

#ifndef __BAMBOOLIB_OPTIONAL_H_
#define __BAMBOOLIB_OPTIONAL_H_


namespace BambooLib
{
	// General template
	template<class T, class Enable = void>
	class optional {
	public:
		using value_type = T;

		optional() : m_pValue(nullptr) {};
		optional(const value_type & val) : m_pValue(new value_type(val)) {};
		optional(value_type && val) : m_pValue(new value_type(val)) {};
		optional(const optional &rOther) : m_pValue(rOther.is_set() ? new value_type(*(rOther.m_pValue)) : nullptr) {};
		optional(optional &&rOther) : m_pValue(rOther.m_pValue) { rOther.m_pValue = nullptr; };
		
		//template <typename... Args> optional(Args&&... args) : m_pValue(new T(std::forward<Args>(args)...)) {};

		value_type& operator=(const value_type &rOther) { reset(); if (rOther.m_pValue != nullptr) m_pValue = new value_type(*(rOther.m_pValue)); };
		value_type& operator=(value_type&& rOther) { reset(); m_pValue = rOther.m_pValue; };
		~optional() { reset(); }

		void reset() { delete m_pValue; m_pValue = nullptr; }
		void set(const value_type & val) { reset(); m_pValue = new value_type(val); }
		void set(value_type && val) { reset(); m_pValue = new value_type(val); }
		bool is_set() const { return (m_pValue != nullptr); }

		value_type & get() { assert(is_set()); return *m_pValue; }
		value_type & operator * () { return get(); };
		value_type * operator -> () { return m_pValue; };

		operator bool() const { return is_set(); };
	private:
		value_type * m_pValue;
	};

	// Specialization for types, which are trivially constructible: Place value on stack
	template<class T>
	class optional<T, typename std::enable_if<std::is_trivially_constructible<T>::value>::type> {
	public:
		using value_type = T;

		optional() : m_isInitialized(false) {};
		optional(const value_type & val) : m_value(val), m_isInitialized(true) {};
		optional(value_type && val) : m_value(val), m_isInitialized(true) {};

		void reset() { m_isInitialized = false; }
		void set(const value_type & val) { m_value = val; m_isInitialized = true; }
		bool is_set() const { return m_isInitialized; }

		value_type & get() { assert(m_isInitialized); return m_value; }
		value_type & operator * () { return get(); };

		operator bool() const { return is_set(); };

	private:
		value_type m_value;
		bool m_isInitialized;
	};
};

#endif