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
        std::vector<size_t> reverse_map;
        std::vector<size_t> augmenting_path;
    public:
        min_cost_max_flow(): adj(), edg(), map(), augmenting_path() {}
        void add_edge(size_t src, size_t tar, const CapType cap, const CostType cost)
        {
            if (!map.count(src))
            {
                map.emplace(src, map.size());
                reverse_map.push_back(src);
                adj.emplace_back();
            }
            if (!map.count(tar))
            {
                map.emplace(tar, map.size());
                reverse_map.push_back(tar);
                adj.emplace_back();
            }
            src = map.at(src); tar = map.at(tar);
            adj[src].push_back(edg.size());
            edg.emplace_back(tar, cap, cost);
            adj[tar].push_back(edg.size());
            edg.emplace_back(src, 0, -cost);
        }
        std::pair<CapType, CostType> __find_augmenting_path(size_t source, size_t sink)
        {
            if (!map.count(source) || !map.count(sink))
                return std::make_pair(CapType(), CostType());
            source = map.at(source); sink = map.at(sink);
            std::vector<bool> in_queue(map.size(), false);
            std::vector<size_t> trace(map.size(), std::numeric_limits<size_t>::max());
            std::vector<CapType> cap(map.size(), CapType());
            std::vector<CostType> cost(map.size(), std::numeric_limits<CostType>::max());
            std::queue<size_t> queue;
            cap[source] = std::numeric_limits<CapType>::max();
            cost[source] = CostType();
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
            if (cap[sink] != CapType())
                for (int cur = sink; cur != source; cur = edg[trace[cur] ^ 1].tar)
                    augmenting_path.push_back(trace[cur]);
            return std::make_pair(cap[sink], cost[sink]);
        }
        void __push_augmenting_path()
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
        std::pair<CapType, CostType> get_min_cost_max_flow(size_t source, size_t sink)
        {
            std::pair<CapType, CostType> result(0, 0), tmp;
            while ((tmp = __find_augmenting_path(source, sink)).first != 0)
            {
                result.first += tmp.first;
                result.second += tmp.first * tmp.second;
                __push_augmenting_path();
            }
            return result;
        }
        std::pair<CapType, CostType> get_min_cost_flow(size_t source, size_t sink)
        {
            std::pair<CapType, CostType> result(0, 0), tmp;
            while ((tmp = __find_augmenting_path(source, sink)).second != 0)
            {
                result.first += tmp.first;
                result.second += tmp.first * tmp.second;
                __push_augmenting_path();
            }
            return result;
        }
        std::vector<std::pair<size_t, CapType>> get_flow_network() const
        {
            std::vector<std::pair<size_t, CapType>> vec;
            for (size_t i = 1; i < edg.size(); i += 2)
                vec.emplace_back(i >> 1, edg.at(i).cap);
            return vec;
        }
    };
}