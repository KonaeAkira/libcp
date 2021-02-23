#include <random>
#include <chrono>
// https://github.com/KonaeAkira/libcp/include/random.hpp/
std::mt19937 RAND_GEN(std::chrono::steady_clock::now().time_since_epoch().count());
uint64_t rand() { return std::uniform_int_distribution<uint64_t>(0, std::numeric_limits<uint64_t>::max())(RAND_GEN); }
uint64_t rand(const uint64_t hi) { return std::uniform_int_distribution<uint64_t>(0, hi)(RAND_GEN); }
uint64_t rand(const uint64_t lo, const uint64_t hi) { return std::uniform_int_distribution<uint64_t>(lo, hi)(RAND_GEN); }
