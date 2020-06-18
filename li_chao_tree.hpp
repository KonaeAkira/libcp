#ifndef LI_CHAO_TREE_HPP
#define LI_CHAO_TREE_HPP
namespace libcp
{
	template<class T, T LO, T HI>
	class li_chao_tree
	{
	private:
		static const T INF = std::numeric_limits<T>::max();
		struct node;
		std::vector<node> vec;
		static T eval(const std::pair<T, T> func, T x)
		{
			return func.first * x + func.second;
		}
		struct node
		{
			std::pair<T, T> func;
			size_t lft, rgt;
			node(const std::pair<T, T> func): func(func), lft(-1), rgt(-1) {}
		};
		void update(const size_t i, const T lo, const T hi, std::pair<T, T> func)
		{
			bool cmp_lft = eval(func, lo) < eval(vec[i].func, lo);
			bool cmp_mid = eval(func, (lo + hi) / 2) < eval(vec[i].func, (lo + hi) / 2);
			if (cmp_mid) std::swap(func, vec[i].func);
			if (lo + 1 != hi)
				if (cmp_lft ^ cmp_mid)
				{
					if (vec[i].lft == -1)
					{
						vec[i].lft = vec.size();
						vec.emplace_back(vec[i].func);
					}
					update(vec[i].lft, lo, (lo + hi) / 2, func);
				}
				else
				{
					if (vec[i].rgt == -1)
					{
						vec[i].rgt = vec.size();
						vec.emplace_back(vec[i].func);
					}
					update(vec[i].rgt, (lo + hi) / 2, hi, func);
				}
		}
		T query(const size_t i, const T lo, const T hi, const T x) const
		{
			if (x < (lo + hi) / 2 && vec[i].lft != -1) return std::min(eval(vec[i].func, x), query(vec[i].lft, lo, (lo + hi) / 2, x));
			else if (x >= (lo + hi) / 2 && vec[i].rgt != -1) return std::min(eval(vec[i].func, x), query(vec[i].rgt, (lo + hi) / 2, hi, x));
			else return eval(vec[i].func, x);
		}
	public:
		li_chao_tree(): vec(1, node(std::make_pair((T)0, INF))) {}
		void insert(const std::pair<T, T> func)
		{
			update(0, LO, HI, func);
		}
		void insert(const T a, const T b)
		{
			update(0, LO, HI, std::make_pair(a, b));
		}
		void insert(const li_chao_tree<T, LO, HI> &tree)
		{
			for (size_t i = 0; i < tree.vec.size(); ++i)
				update(0, LO, HI, tree.vec[i].func);
		}
		T query(const T x) const
		{
			assert(x >= LO && x < HI);
			return query(0, LO, HI, x);
		}
		size_t size() const
		{
			return vec.size();
		}
	};
}
#endif