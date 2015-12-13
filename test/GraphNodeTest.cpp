#include <gtest/gtest.h>
#include "GraphNode.h"

using namespace BambooLib;

class TestType : public GraphNode<TestType>
{
public:
	TestType(int value) : m_value(value) {};
	~TestType() { std::cout << "Destroyed" << std::endl; }

	int getValue() const { return m_value; }
private:
	int m_value;
};

TEST(GraphNode, AddNode)
{
	auto node1 = std::make_shared<TestType>(10);
	auto node2 = std::make_shared<TestType>(5);

	node1->addChild(node2);

	ASSERT_EQ(node1->numChildren(), 1);
	ASSERT_EQ(node1->getChildren()[0], node2);
}

TEST(GraphNode, AddMultipleNodes)
{
	auto root_node = std::make_shared<TestType>(999);

	{
		auto node1 = std::make_shared<TestType>(1);
		auto node2 = std::make_shared<TestType>(2);
		auto node3 = std::make_shared<TestType>(3);
		auto node4 = std::make_shared<TestType>(4);
		auto node5 = std::make_shared<TestType>(5);
		auto node6 = std::make_shared<TestType>(6);
		auto node7 = std::make_shared<TestType>(7);
		auto node8 = std::make_shared<TestType>(8);
		auto node9 = std::make_shared<TestType>(9);

		root_node->addChild(node1);
		root_node->addChild(node2);
		root_node->addChild(node3);
		root_node->addChild(node4);
		root_node->addChild(node5);
		root_node->addChild(node6);
		root_node->addChild(node7);
		root_node->addChild(node8);
		root_node->addChild(node9);
	}

	ASSERT_EQ(root_node->numChildren(), 9);
}

TEST(GraphNode, GetChildrenNodes)
{
	auto root_node = std::make_shared<TestType>(999);

	{
		auto node1 = std::make_shared<TestType>(1);
		auto node2 = std::make_shared<TestType>(2);
		auto node3 = std::make_shared<TestType>(3);
		auto node4 = std::make_shared<TestType>(4);
		auto node5 = std::make_shared<TestType>(5);
		auto node6 = std::make_shared<TestType>(6);
		auto node7 = std::make_shared<TestType>(7);
		auto node8 = std::make_shared<TestType>(8);
		auto node9 = std::make_shared<TestType>(9);

		root_node->addChild(node1);
		root_node->addChild(node2);
		root_node->addChild(node3);
		root_node->addChild(node4);
		root_node->addChild(node5);
		root_node->addChild(node6);
		root_node->addChild(node7);
		root_node->addChild(node8);
		root_node->addChild(node9);
	}

	ASSERT_EQ(root_node->numChildren(), 9);

	auto children = root_node->getChildren();
	root_node->removeChild(children[0]);

	ASSERT_EQ(root_node->numChildren(), 8);
}

TEST(GraphNode, AddNode_Double)
{
	auto node1 = std::make_shared<TestType>(10);
	auto node2 = std::make_shared<TestType>(5);

	bool ok1 = node1->addChild(node2);
	ASSERT_TRUE(ok1);

	bool ok2 = node1->addChild(node2);
	ASSERT_FALSE(ok2);

	ASSERT_EQ(node1->numChildren(), 1);
}

TEST(GraphNode, RemoveNode)
{
	auto node1 = std::make_shared<TestType>(10);
	auto node2 = std::make_shared<TestType>(5);

	bool ok1 = node1->addChild(node2);
	bool ok2 = node1->removeChild(node2);
	ASSERT_TRUE(ok1);
	ASSERT_TRUE(ok2);

	ASSERT_EQ(node1->numChildren(), 0);
}

TEST(GraphNode, RemoveNode_WrongUsage)
{
	auto node1 = std::make_shared<TestType>(10);
	auto node2 = std::make_shared<TestType>(5);

	bool ok1 = node1->addChild(node2);
	bool ok2 = node1->removeChild(node2);
	ASSERT_TRUE(ok1);
	ASSERT_TRUE(ok2);

	ASSERT_EQ(node1->numChildren(), 0);

	bool ok3 = node1->removeChild(node2);
	ASSERT_FALSE(ok3);

	ASSERT_EQ(node1->numChildren(), 0);
}

TEST(GraphNode, Clear)
{
	auto node1 = std::make_shared<TestType>(10);
	auto node2 = std::make_shared<TestType>(5);

	node1->addChild(node2);

	ASSERT_EQ(node1->numChildren(), 1);
	node1->clearChildren();

	ASSERT_EQ(node1->numChildren(), 0);
}