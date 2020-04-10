// sparse_fenwick_tree
#include <cassert>
#include <functional>
#include <unordered_map>
namespace libcp
{
	template<size_t Size, class Type, class Op = std::plus<Type>, Type Neut = Type()>
	class sparse_fenwick_tree
	{
	private:
		std::unordered_map<size_t, Type> map;
		Op op;
		Type get(size_t p) const
		{
			if (!map.count(p))
				return Neut;
			else
				return map[p];
		}
	public:
		sparse_fenwick_tree(): op(), map() {}
		void update(size_t p, const Type &v)
		{
			++p;
			assert(p >= 0 && p <= Size);
			while (p <= Size)
			{
				if (map.count(p))
					map[p] = op(std::move(map.at(p)), v);
				else
					map[p] = v;
				p += p & -p;
			}
		}
		Type query(size_t p) const
		{
			++p;
			assert(p >= 0 && p <= Size);
			Type res = Neut;
			while (p > 0)
			{
				if (map.count(p))
					res = op(std::move(res), map.at(p));
				p -= p & -p;
			}
			return res;
		}
		void clear()
		{
			map.clear();
		}
	};
}
