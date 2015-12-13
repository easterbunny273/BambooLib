#pragma once
#ifndef __BAMBOOLIB_GRAPHNODE_H_
#define __BAMBOOLIB_GRAPHNODE_H_

#include <vector>
#include <algorithm>
#include <memory>

namespace BambooLib
{
	template <class T> class GraphNode
	{
	public:
		using SharedPtr = std::shared_ptr<T>;

		bool addChild(SharedPtr child)
		{
			bool ok = hasChild(child) == false;
			
			if (ok)
				m_children.push_back(child);

			return ok;
		};

		bool removeChild(SharedPtr child)
		{
			auto iter = std::find(m_children.begin(), m_children.end(), child);
			bool ok = iter != m_children.end();

			if (ok)
				m_children.erase(iter);

			return ok;
		};

		bool hasChild(SharedPtr child) const { return std::find(m_children.begin(), m_children.end(), child) != m_children.end(); };
		void clearChildren() { m_children.clear(); };
		auto numChildren() const { return m_children.size(); };

		const std::vector<SharedPtr> & getChildren() const { return m_children; };

	private:
		std::vector<SharedPtr>	m_children;
	};
};

#endif
