#ifndef RANDOM_HPP
#define RANDOM_HPP
namespace libcp
{
    namespace random
    {
        const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        uint64_t rand() { return std::uniform_int_distribution<uint64_t>(0, std::numeric_limits<uint64_t>::max())(generator); }
        uint64_t rand(const uint64_t hi) { return std::uniform_int_distribution<uint64_t>(0, hi)(generator); }
        uint64_t rand(const uint64_t lo, const uint64_t hi) { return std::uniform_int_distribution<uint64_t>(lo, hi)(generator); }
    }
}
#endif