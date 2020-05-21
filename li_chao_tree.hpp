/ li_chao_tree
#include <algorithm>
#include <limits>
namespace libcp
{
	template<class FT, FT LO, FT HI>
	class li_chao_tree
	{
	private:
		std::pair<FT, FT> arr[(HI - LO) * 4];
		FT value(std::pair<FT, FT> cur, FT x) const
		{
			return cur.first * x + cur.second;
		}
	public:
		li_chao_tree()
		{
			for (auto &dat : arr)
			{
				dat.first = 0;
				dat.second = std::numeric_limits<FT>::max() / 4;
			}
		}
		void clear()
		{
			for (auto &dat : arr)
			{
				dat.first = 0;
				dat.second = std::numeric_limits<FT>::max() / 4;
			}
		}
		void add_line(std::pair<FT, FT> cur, size_t p = 0, FT lo = LO, FT hi = HI)
		{
			FT mid = (lo + hi) / 2;
			bool comp_lft = value(cur, lo) < value(arr[p], lo);
			bool comp_mid = value(cur, mid) < value(arr[p], mid);
			if (comp_mid)
				std::swap(cur, arr[p]);
			if (lo + 1 != hi)
			{
				if (comp_lft ^ comp_mid)
					add_line(cur, p * 2 + 1, lo, mid);
				else
					add_line(cur, p * 2 + 2, mid, hi);
			}
		}
		void add_line(FT a, FT b)
		{
			add_line(std::make_pair(a, b));
		}
		FT get(FT x, size_t p = 0, FT lo = LO, FT hi = HI) const
		{
			if (lo + 1 == hi)
				return value(arr[p], x);
			FT mid = (lo + hi) / 2;
			if (x < mid)
				return std::min(value(arr[p], x), get(x, p * 2 + 1, lo, mid));
			else
				return std::min(value(arr[p], x), get(x, p * 2 + 2, mid, hi));
		}
	};
}
