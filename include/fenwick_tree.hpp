// fenwick_tree
#include <cassert>
#include <functional>
namespace libcp
{
	template<size_t Size, class Type, class Op = std::plus<Type>, Type Init = Type()>
	class fenwick_tree
	{
	private:
		Type arr[Size];
		Op op;
	public:
		fenwick_tree(): op()
		{
			for (int i = 0; i < Size; ++i)
				arr[i] = Init;
		}
		void update(size_t p, const Type &v)
		{
			assert(p >= 0 && p < Size);
			while (p < Size)
			{
				arr[p] = op(std::move(arr[p]), v);
				p += p & -p;
			}
		}
		Type query(size_t p) const
		{
			assert(p >= 0 && p < Size);
			Type res = Init;
			while (p > 0)
			{
				res = op(std::move(res), arr[p]);
				p -= p & -p;
			}
			return res;
		}
	};
}
