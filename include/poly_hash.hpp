// poly_hash
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdint>
namespace libcp
{	
	class poly_hash
	{
	private:
		static const uint64_t base = 257;
		static uint64_t mod;
		static std::vector<uint64_t> basepow;
		static void init()
		{
			uint64_t mod_list[] = {1, 19, 61, 69, 85, 99, 105, 151, 159, 171};
			srand(time(NULL));
			mod = (1LL << 31) - mod_list[rand() % 10];
			basepow = std::vector<uint64_t>(1, 1);
		}
		void extend(size_t n)
		{
			if (mod == 0)
				init();
			if (n >= basepow.size())
			{
				size_t m = basepow.size();
				basepow.resize(n + 1);
				for (size_t i = m; i <= n; ++i)
					basepow[i] = basepow[i - 1] * base % mod;
			}
		}
		std::vector<uint64_t> vec;
	public:
		poly_hash(const char *str)
		{
			size_t n = strlen(str);
			extend(n);
			vec.resize(n + 1);
			vec[0] = 0;
			for (size_t i = 0; i < n; ++i)
				vec[i + 1] = (vec[i] * base + str[i]) % mod;
		}
		poly_hash(char *str)
		{
			size_t n = strlen(str);
			extend(n);
			vec.resize(n + 1);
			vec[0] = 0;
			for (size_t i = 0; i < n; ++i)
				vec[i + 1] = (vec[i] * base + str[i]) % mod;
		}
		poly_hash(const std::string &str)
		{
			size_t n = str.size();
			extend(n);
			vec.resize(n + 1);
			vec[0] = 0;
			for (size_t i = 0; i < n; ++i)
				vec[i + 1] = (vec[i] * base + str[i]) % mod;
		}
		size_t size() const
		{
			return vec.size();
		}
		uint64_t get_hash() const
		{
			return vec.back();
		}
		uint64_t get_hash(size_t i, size_t j) const
		{
			assert(i <= j && i >= 0 && j < vec.size());
			uint64_t tmp = vec[j] - vec[i] * basepow[j - i] % mod;
			return tmp < mod ? tmp : mod + tmp;
		}
	};
	uint64_t poly_hash::mod = 0;
	std::vector<uint64_t> poly_hash::basepow = std::vector<uint64_t>(1, 1);
}
