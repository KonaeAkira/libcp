// sparse_li_chao_tree
#include <algorithm>
#include <limits>
#include <cassert>
namespace libcp
{
	template<class FT, FT LO, FT HI>
	class sparse_li_chao_tree
	{
	private:
		static const FT INF = std::numeric_limits<FT>::max();
		static FT eval(const std::pair<FT, FT> dat, FT x)
		{
			return dat.first * x + dat.second;
		}
		struct node
		{
			FT lo, hi;
			std::pair<FT, FT> dat;
			node *lft, *rgt;
			node(const FT lo, const FT hi, const std::pair<FT, FT> dat = std::make_pair(0, INF)):
				lo(lo), hi(hi), dat(dat), lft(nullptr), rgt(nullptr) {}
			void update(std::pair<FT, FT> nxt)
			{
				bool cmp_lft = eval(nxt, lo) < eval(dat, lo);
				bool cmp_mid = eval(nxt, (lo + hi) / 2) < eval(dat, (lo + hi) / 2);
				if (cmp_mid)
					std::swap(nxt, dat);
				if (lo + 1 != hi)
					if (cmp_lft ^ cmp_mid)
					{
						if (lft == nullptr)
							lft = new node(lo, (lo + hi) / 2, dat);
						lft->update(nxt);
					}
					else
					{
						if (rgt == nullptr)
							rgt = new node((lo + hi) / 2, hi, dat);
						rgt->update(nxt);
					}
			}
			FT query(const FT x) const
			{
				if (x < (lo + hi) / 2 && lft != nullptr)
					return std::min(eval(dat, x), lft->query(x));
				else if (x >= (lo + hi) / 2 && rgt != nullptr)
					return std::min(eval(dat, x), rgt->query(x));
				else
					return eval(dat, x);
			}
		} root;
	public:
		sparse_li_chao_tree(): root(LO, HI) {}
		void update(const std::pair<FT, FT> dat)
		{
			root.update(dat);
		}
		void update(const FT a, const FT b)
		{
			root.update(std::make_pair(a, b));
		}
		FT query(const FT x) const
		{
			assert(x >= LO && x < HI);
			return root.query(x);
		}
	};
}
