// fenwick_tree
#include <cassert>
#include <functional>
#include <algorithm>
namespace libcp
{
	template<size_t Size, class Type, class Op = std::plus<Type>, Type Neut = Type()>
	class fenwick_tree
	{
	private:
		Type arr[Size + 1];
		Op op;
	public:
		fenwick_tree(): op()
		{
			std::fill(arr, arr + Size + 1, Neut);
		}
		void update(size_t p, const Type &v)
		{
			++p;
			assert(p >= 0 && p <= Size);
			while (p <= Size)
			{
				arr[p] = op(std::move(arr[p]), v);
				p += p & -p;
			}
		}
		Type query(size_t p) const
		{
			++p;
			assert(p >= 0 && p < Size);
			Type res = Neut;
			while (p > 0)
			{
				res = op(std::move(res), arr[p]);
				p -= p & -p;
			}
			return res;
		}
		void clear(size_t n = Size)
		{
			std::fill(arr + 1, arr + n + 1, Neut);
		}
	};
}
