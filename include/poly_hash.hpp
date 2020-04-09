// poly_hash
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <cassert>
#include <cstring>
#include <cstdint>
namespace libcp
{
	class poly_hash
	{
	private:
		static const uint64_t mod = 2147483647;
		static uint64_t base;
		static std::vector<uint64_t> basepow;
		static void generate_base()
		{
			unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed);
			base = std::uniform_int_distribution<int>(256, 1048576)(generator);
		}
		static void extend(size_t n)
		{
			if (base == 0)
				generate_base();
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
		poly_hash(): vec() {}
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
		uint64_t get_hash(size_t i) const
		{
			assert(i >= 0 && i < vec.size());
			return vec[i];
		}
		uint64_t get_hash(size_t i, size_t j) const
		{
			assert(i <= j && i >= 0 && j < vec.size());
			uint64_t tmp = vec[j] - vec[i] * basepow[j - i] % mod;
			return tmp < mod ? tmp : mod + tmp;
		}
	};
	uint64_t poly_hash::base = 0;
	std::vector<uint64_t> poly_hash::basepow = std::vector<uint64_t>(1, 1);
	bool operator < (const poly_hash &lhs, const poly_hash &rhs)
	{
		size_t n = std::min(lhs.size(), rhs.size());
		size_t s = 1;
		while (s << 1 < n)
			s <<= 1;
		for (; s; s >>= 1)
			if (n > s && lhs.get_hash(n - s) != rhs.get_hash(n - s))
				n -= s;
		if (n == std::min(lhs.size(), rhs.size()))
			return lhs.size() < rhs.size();
		else
			return lhs.get_hash(n - 1, n) < rhs.get_hash(n - 1, n);
	}
}
