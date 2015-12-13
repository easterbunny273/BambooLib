#pragma once

#ifndef __BAMBOOLIB_VARIANT_H_
#define __BAMBOOLIB_VARIANT_H_

#include <string>
#include <cassert>
#include <memory>
#include <typeinfo>
#include <vector>

namespace BambooLib
{

	class Variant
	{
	public:
		enum class EType
		{
			BOOLEAN,
			INTEGER,
			DOUBLE,
			STRING,
			VARIANT_VECTOR,
			UNKNOWN,

			NUM_TYPES
		};


	private:
		class TItlValue
		{
		public:
			template<class T> T& get() const 
			{			
				if (typeid(T) != getTypeId())
					throw std::exception("variant holds different type");

				return *(T*)getRawData();
			};

			template<class T> T& get()
			{
				if (typeid(T) != getTypeId())
					throw std::exception("variant holds different type");

				return *(T*)getRawData();
			};

			template <class T> bool get(T &rValue)
			{
				bool correctType = (typeid(T) == getTypeId());

				if (correctType)
					rValue = *(T*)getRawData();

				return correctType;
			}

			template <class T> bool get(const T &rValue) const
			{
				bool correctType = (typeid(T) == getTypeId());

				if (correctType)
					rValue = *(T*)getRawData();

				return correctType;
			}

			template<class T> bool set(const T& value)
			{
				bool correctType = (typeid(T) == getTypeId());

				if (correctType)
					get<T>() = value;

				return correctType;
			}

			virtual const std::type_info & getTypeId() const = 0;
			virtual std::unique_ptr<TItlValue> clone() const = 0;

			bool operator==(const TItlValue &other) const { return equals(other); }
		protected:
			virtual bool equals(const TItlValue &other) const = 0;
			virtual const void * getRawData() const = 0;
			virtual void * getRawData() = 0;
		};

		template <class T> class TItlConcreteValue : public TItlValue
		{
		public:
			TItlConcreteValue(T value) : m_value(value) {};

			virtual const std::type_info & getTypeId() const { return typeid(m_value); };
			virtual std::unique_ptr<TItlValue> clone() const { return std::unique_ptr<TItlValue>(new TItlConcreteValue<T>(m_value)); }

			
		protected:
			virtual const void * getRawData() const { return (const void*) &m_value; }
			virtual void * getRawData() { return (void*)&m_value; }
			virtual T getValue() const { return m_value; }
			virtual T getValue(T) const { return m_value; }

			virtual bool equals(const TItlValue &other) const
			{
				auto otherAsSameConcrete = dynamic_cast<const TItlConcreteValue<T> *>(&other);

				if (otherAsSameConcrete)
					return (m_value == otherAsSameConcrete->m_value);
				else
					return false;
			}

		private:
			T m_value;
		};

		EType m_type;
		std::unique_ptr<TItlValue> m_valueImpl;

	public:

		/*variant(const char * cstring) : m_type(EType::STRING), m_valueImpl(new TItlConcreteValue<std::string>(cstring)) {};
		template <class T> variant(const T& value) : m_type(EType::UNKNOWN), m_valueImpl(new TItlConcreteValue<T>(value)) {};*/
		
		Variant(bool value) : m_type(EType::BOOLEAN), m_valueImpl(new TItlConcreteValue<bool>(value)) {};
		Variant(double value) : m_type(EType::DOUBLE), m_valueImpl(new TItlConcreteValue<double>(value)) {};
		Variant(int value) : m_type(EType::INTEGER), m_valueImpl(new TItlConcreteValue<int>(value)) {};
		Variant(const std::string & value) : m_type(EType::STRING), m_valueImpl(new TItlConcreteValue<std::string>(value)) {};
		Variant(const char * cstring) : m_type(EType::STRING), m_valueImpl(new TItlConcreteValue<std::string>(cstring)) {};
		Variant(const std::vector<Variant> & value) : m_type(EType::VARIANT_VECTOR), m_valueImpl(new TItlConcreteValue<std::vector<Variant>>(value)) {};

		Variant(const Variant &other) : m_type(other.m_type), m_valueImpl(other.m_valueImpl->clone()) {};
		Variant(Variant && other) : m_type(other.m_type), m_valueImpl(std::move(other.m_valueImpl)) {};

		Variant & operator=(const Variant &other) { m_type = other.m_type; m_valueImpl = other.m_valueImpl->clone(); return *this; }
		Variant & operator=(Variant &&other) { m_type = other.m_type; m_valueImpl = std::move(other.m_valueImpl); return *this; }

		template <class T> const T& get() const { return m_valueImpl->get<T>(); }
		template <class T> T& get() { return m_valueImpl->get<T>(); }

		template <class T> bool get(T& rValue) const { return m_valueImpl->get<T>(rValue); }
		template <class T> bool get(T& rValue) { return m_valueImpl->get<T>(rValue); }

		template <class T> bool set(const T& value) { return m_valueImpl->set<T>(value); }

		bool operator==(const Variant &other) const
		{
			return (m_type == other.m_type && (*m_valueImpl == *other.m_valueImpl));
		}

		EType getType() const { return m_type; };
		const std::type_info & getTypeId() const { return m_valueImpl->getTypeId(); }
	};
};

#endif