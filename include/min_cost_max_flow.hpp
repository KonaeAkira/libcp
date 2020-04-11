// min_cost_max_flow
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
namespace libcp
{
	template<class CapType, class CostType>
	class min_cost_max_flow
	{
	private:
		unsigned n;
		std::vector<std::vector<unsigned>> adj;
		struct edge { unsigned ind; CapType cap; CostType cost; };
		std::vector<edge> data;
		void extend(unsigned m)
		{
			n = m;
			adj.resize(m);
		}
	public:
		min_cost_max_flow(): n(), adj(), data() {}
		min_cost_max_flow(unsigned n): n(n), adj(n), data() {}
		void add_edge(unsigned src, unsigned tar, CapType cap, CostType cost)
		{
			if (std::max(src, tar) >= n)
				extend(std::max(src, tar));
			adj[src].push_back(data.size());
			data.push_back({tar, cap, cost});
			adj[tar].push_back(data.size());
			data.push_back({src, 0, -cost});
		}
		std::pair<CapType, CostType> augment(unsigned src, unsigned tar)
		{
			assert(src < n && tar < n);
			std::vector<edge> trace(n, {0, 0, std::numeric_limits<CostType>::max()});
			std::vector<bool> in_queue(n);
			std::queue<unsigned> queue;
			trace[src] = {0, std::numeric_limits<CapType>::max(), 0};
			queue.push(src);
			unsigned cur, nxt;
			while (!queue.empty())
			{
				cur = queue.front();
				in_queue[cur] = false;
				queue.pop();
				for (unsigned edg : adj[cur])
				{
					nxt = data[edg].ind;
					if (data[edg].cap != 0 && trace[cur].cost + data[edg].cost < trace[nxt].cost)
					{
						trace[nxt].ind = edg;
						trace[nxt].cap = std::min(trace[cur].cap, data[edg].cap);
						trace[nxt].cost = trace[cur].cost + data[edg].cost;
						if (!in_queue[nxt])
						{
							in_queue[nxt] = true;
							queue.push(nxt);
						}
					}
				}
			}
			if (trace[tar].cap == 0)
				return {0, std::numeric_limits<CostType>::max()};
			CapType cap = trace[tar].cap;
			CostType cost = trace[tar].cost;
			for (unsigned i = tar; i != src; i = data[trace[i].ind ^ 1].ind)
			{
				data[trace[i].ind].cap -= cap;
				data[trace[i].ind ^ 1].cap += cap;
			}
			return {cap, cost};
		}
	};
}
