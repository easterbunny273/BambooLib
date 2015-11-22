#include "gtest/gtest.h"
#include "optional.h"

class SampleComplexType
{
public:
	SampleComplexType(double val, int val2, int *counter=nullptr) : m_val(val), m_val2(val2), m_pCounter(counter) 
	{ 
		if (m_pCounter) 
			(*m_pCounter)++; 
	};

	~SampleComplexType() 
	{ 
		if (m_pCounter) 
			(*m_pCounter)--; 
	}

	SampleComplexType(const SampleComplexType & other) 
	{ 
		m_val = other.m_val;  m_val2 = other.m_val2; m_pCounter = other.m_pCounter; 
		if (m_pCounter) 
			(*m_pCounter)++; 
	}
	
	auto getVal() const { return m_val; }
	auto getVal2() const { return m_val2; }

private:
	double m_val; int m_val2;
	int * m_pCounter;
};

TEST(Optional, SimpleType)
{
	BambooLib::optional<int> object;

	EXPECT_FALSE(object.is_set());

	object.set(5);

	EXPECT_TRUE(object.is_set());
	EXPECT_EQ(object.get(), 5);
}

TEST(Optional, SimpleTypeReset)
{
	BambooLib::optional<int> object(5);

	EXPECT_TRUE(object.is_set());

	object.reset();

	EXPECT_FALSE(object.is_set());
}

TEST(Optional, AssertsGetOnNotSetInt)
{
	BambooLib::optional<int> object;

	EXPECT_DEATH(object.get(), "m_isInitialized");
}

TEST(Optional, ComplexType)
{
	BambooLib::optional<SampleComplexType> object(SampleComplexType(4.0, 15));

	EXPECT_TRUE(object.is_set());

	EXPECT_EQ(object.get().getVal(), 4.0);
	EXPECT_EQ(object.get().getVal2(), 15);
}

TEST(Optional, ComplexType_ForwardConstructor)
{
	BambooLib::optional<SampleComplexType> object(SampleComplexType(4.0, 15));

	EXPECT_TRUE(object.is_set());

	EXPECT_EQ(object.get().getVal(), 4.0);
	EXPECT_EQ(object.get().getVal2(), 15);
}

TEST(Optional, ComplexType_ForwardSet)
{
	BambooLib::optional<SampleComplexType> object;

	EXPECT_FALSE(object.is_set());

	object.set(SampleComplexType(3.0, 16));

	EXPECT_TRUE(object.is_set());
	EXPECT_EQ(object.get().getVal(), 3.0);
	EXPECT_EQ(object.get().getVal2(), 16);
}

TEST(Optional, ComplexType_OperatorPtr)
{
	BambooLib::optional<SampleComplexType> object(SampleComplexType(2.0, 14));

	EXPECT_TRUE(object.is_set());

	EXPECT_EQ((*object).getVal(), 2.0);
	EXPECT_EQ(object->getVal(), 2.0);
	EXPECT_EQ(object->getVal2(), 14.0);
}

TEST(Optional, ComplexType_MemoryManagment)
{
	int counter = 0;
	EXPECT_EQ(counter, 0);

	{
		BambooLib::optional<SampleComplexType> object(SampleComplexType(2.0, 14, &counter));
		EXPECT_EQ(counter, 1);

		{
			BambooLib::optional<SampleComplexType> object2;
			EXPECT_EQ(counter, 1);

			object2.set(SampleComplexType(3.0, 15, &counter));

			EXPECT_EQ(counter, 2);
		}

		EXPECT_EQ(counter, 1);
		
	}

	{
		BambooLib::optional<SampleComplexType> object(SampleComplexType(2.0, 14, &counter));
		EXPECT_EQ(counter, 1);

		BambooLib::optional<SampleComplexType> object2(object);

		EXPECT_EQ(counter, 2);

		BambooLib::optional<SampleComplexType> object3(object);

		EXPECT_EQ(counter, 3);
	}
	
	EXPECT_EQ(counter, 0);
}