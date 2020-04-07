// data_index
#include <cassert>
#include <map>
#include <functional>
namespace libcp
{
	template<typename T, class C = std::less<T>>
	class data_index
	{
	private:
		std::map<T, size_t, C> map;
		bool finalized;
	public:
		data_index(): map(), finalized() {}
		void insert(T e)
		{
			assert(!finalized);
			map.emplace(e, 0);
		}
		void finalize()
		{
			assert(!finalized);
			finalized = true;
			size_t cnt = 0;
			for (auto &i : map)
				i.second = cnt++;
		}
		size_t get_index(T e)
		{
			assert(finalized);
			return map[e];
		}
	};
}
