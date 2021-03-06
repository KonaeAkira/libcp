#include "random.hpp"
#include "modular_arithmetic.hpp"
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
// https://github.com/KonaeAkira/libcp/blob/master/include/string_hash.hpp
typedef modular_number<uint64_t, 1000000009> hash_num_t;
const hash_num_t HASH_BASE(rand(256, 65536));
std::vector<hash_num_t> HASH_BASE_POW(1, 1);
class string_hash
{
private:
	std::vector<hash_num_t> data;
	void construct_vector(const std::string &str)
	{
		data.clear();
		data.reserve(str.size() + 1);
		data.push_back(0);
		for (char c : str)
			data.push_back(data.back() * HASH_BASE + c);
		while (HASH_BASE_POW.size() < data.size())
			HASH_BASE_POW.push_back(HASH_BASE_POW.back() * HASH_BASE);
	}
public:
	string_hash(): data(1, 0) {}
	string_hash(const std::string &str) { construct_vector(str); }
	string_hash &operator = (const std::string &str) { construct_vector(str); return *this; }
	size_t size() const { return data.size() - 1; } // string size
	uint64_t get() const { return data.back().get(); }
	uint64_t get(const size_t l, const size_t r) const // string-indexed, [l, r)
	{
		assert(l <= r && r < data.size());
		return (data.at(r) - data.at(l) * HASH_BASE_POW.at(r - l)).get();
	}
};
std::istream &operator >> (std::istream &stream, string_hash &rhs)
{
	std::string tmp;
	std::cin >> tmp;
	rhs = tmp;
    return stream;
}
std::ostream &operator << (std::ostream &stream, const string_hash &rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
		stream << (char)rhs.get(i, i + 1);
    return stream;
}
