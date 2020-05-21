#include <bits/stdc++.h>
// min_cost_max_flow
// tested on CF 1187G
namespace libcp
{
    template<class CapType, class CostType>
    class min_cost_max_flow
    {
    private:
        struct edge
        {
            const size_t tar;
            CapType cap;
            const CostType cost;
            edge(const size_t tar, const CapType cap, const CostType cost): tar(tar), cap(cap), cost(cost) {}
        };
        std::vector<std::vector<size_t>> adj;
        std::vector<edge> edg;
        std::unordered_map<size_t, size_t> map;
        std::vector<size_t> augmenting_path;
    public:
        min_cost_max_flow(): adj(), edg(), map(), augmenting_path() {}
        void add_edge(size_t src, size_t tar, const CapType cap = 1, const CostType cost = 0)
        {
            if (!map.count(src))
            {
                map.emplace(src, map.size());
                adj.emplace_back();
            }
            if (!map.count(tar))
            {
                map.emplace(tar, map.size());
                adj.emplace_back();
            }
            src = map.at(src); tar = map.at(tar);
            adj[src].push_back(edg.size());
            edg.emplace_back(tar, cap, cost);
            adj[tar].push_back(edg.size());
            edg.emplace_back(src, 0, -cost);
        }
        std::pair<CapType, CostType> find_augmenting_path(size_t source, size_t sink)
        {
            assert(map.count(source) && map.count(sink));
            source = map.at(source); sink = map.at(sink);
            std::vector<bool> in_queue(map.size(), false);
            std::vector<size_t> trace(map.size(), std::numeric_limits<size_t>::max());
            std::vector<CapType> cap(map.size(), 0);
            std::vector<CostType> cost(map.size(), std::numeric_limits<CostType>::max());
            std::queue<size_t> queue;
            cap[source] = std::numeric_limits<CapType>::max();
            cost[source] = 0;
            queue.push(source);
            while (!queue.empty())
            {
                size_t cur = queue.front();
                queue.pop();
                in_queue[cur] = false;
                for (const size_t e : adj[cur])
                    if (edg[e].cap != 0 && cost[cur] + edg[e].cost < cost[edg[e].tar])
                    {
                        trace[edg[e].tar] = e;
                        cap[edg[e].tar] = std::min(cap[cur], edg[e].cap);
                        cost[edg[e].tar] = cost[cur] + edg[e].cost;
                        if (!in_queue[edg[e].tar])
                        {
                            queue.push(edg[e].tar);
                            in_queue[edg[e].tar] = true;
                        }
                    }
            }
            augmenting_path.clear();
            if (cap[sink] != 0)
                for (int cur = sink; cur != source; cur = edg[trace[cur] ^ 1].tar)
                    augmenting_path.push_back(trace[cur]);
            return std::make_pair(cap[sink], cost[sink]);
        }
        void push_augmenting_path()
        {
            assert(!augmenting_path.empty());
            CapType cap = std::numeric_limits<CapType>::max();
            for (const size_t e : augmenting_path)
                cap = std::min(cap, edg[e].cap);
            for (const size_t e : augmenting_path)
            {
                edg[e].cap -= cap;
                edg[e ^ 1].cap += cap;
            }
            augmenting_path.clear();
        }
    };
}