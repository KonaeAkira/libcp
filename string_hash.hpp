#ifndef STRING_HASH_HPP
#define STRING_HASH_HPP
#include "random.hpp"
namespace libcp
{
    class string_hash
    {
    private:
        static std::vector<uint64_t> basepow;
        static void extend_basepow(const size_t n)
        {
            if (basepow.size() < n)
            {
                basepow.reserve(n);
                while (basepow.size() != n)
                    basepow.push_back(basepow.back() * BASE % MOD);
            }
        }
        std::vector<uint64_t> data;
    public:
        static const uint64_t MOD = 2147483647;
        static const uint64_t BASE;
        string_hash(): data(1, 0) {}
        string_hash(const libcp::string_hash &org): data(org.data) {}
        string_hash(const std::string &str)
        {
            data = std::vector<uint64_t>(1, 0);
            for (const char c : str)
                data.push_back((data.back() * BASE + c) % MOD);
            extend_basepow(data.size());
        }
        void push(uint64_t c)
        {
            data.push_back((data.back() * BASE + c) % MOD);
            extend_basepow(data.size());
        }
        size_t size() const { return data.size() - 1; }
        uint64_t get(const size_t begin, const size_t end) const
        {
            assert(begin <= end && end < data.size());
            return (data.at(end) - data.at(begin) * basepow.at(end - begin) % MOD + MOD) % MOD;
        }
    };
    const uint64_t string_hash::BASE = random::rand(1 << 20, 1 << 25);
    std::vector<uint64_t> string_hash::basepow = std::vector<uint64_t>(1, 1);
}
#endif