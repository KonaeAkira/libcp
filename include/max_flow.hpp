// max_flow
#include <cassert>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <limits>
namespace libcp
{
	template<class CapType>
	class max_flow
	{
	private:
		std::vector<std::unordered_map<uint16_t, CapType>> map;
	public:
		max_flow(): map() {}
		void clear()
		{
			map.clear();
		}
		void add_edge(uint16_t src, uint16_t tar, CapType cap)
		{
			if (src >= map.size())
				map.resize(src + 1);
			if (tar >= map.size())
				map.resize(tar + 1);
			map[src][tar] += cap;
		}
		CapType push_flow(uint16_t src, uint16_t tar)
		{
			std::unordered_map<uint16_t, uint16_t> trace;
			std::queue<std::pair<uint16_t, CapType>> queue;
			trace[src] = src;
			queue.emplace(src, std::numeric_limits<CapType>::max());
			CapType flow;
			while (!queue.empty())
			{
				for (auto edg : map[queue.front().first])
					if (edg.second && !trace.count(edg.first))
					{
						trace[edg.first] = queue.front().first;
						if (edg.first == tar)
						{
							flow = std::min(queue.front().second, edg.second);
							goto found;
						}
						queue.emplace(edg.first, std::min(queue.front().second, edg.second));
					}
				queue.pop();
			}
			return 0;
		found:
			for (uint16_t i = tar; i != src; i = trace[i])
			{
				map[i][trace[i]] += flow;
				map[trace[i]][i] -= flow;
			}
			return flow;
		}
	};
}
