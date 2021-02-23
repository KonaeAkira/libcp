#include <iostream>
#include <vector>
#include <algorithm>
// https://github.com/KonaeAkira/libcp/include/suffix_array.hpp/
std::vector<size_t> cyclic_array(const std::string &str)
{
	const size_t n = str.size();
	std::vector<size_t> ind(n), wgt(n), cnt(n), tmp(n);
	{
		std::vector<std::pair<char, size_t>> tmp(n);
		for (size_t i = 0; i < n; ++i)
		{
			tmp[i].first = str[i];
			tmp[i].second = i;
		}
		std::sort(tmp.begin(), tmp.end());
		for (size_t i = 0, j = 0; i < n; ++i)
		{
			ind[i] = tmp[i].second;
			if (i && tmp[i - 1].first != tmp[i].first) ++j;
			wgt[tmp[i].second] = j;
		}
	}
	for (size_t k = 1; k < n; k <<= 1)
	{
		std::fill(cnt.begin(), cnt.end(), 0);
		for (size_t i = 0; i < n; ++i)
		{
			tmp[i] = ind[i] >= k ? ind[i] - k : ind[i] + n - k;
			++cnt[wgt[tmp[i]]];
		}
		for (size_t i = 1; i < n; ++i)
			cnt[i] += cnt[i - 1];
		for (size_t i = 1; i <= n; ++i)
			ind[--cnt[wgt[tmp[n - i]]]] = tmp[n - i];
		tmp[ind.front()] = 0;
		for (size_t i = 1; i < n; ++i)
		{
			const size_t l1 = ind[i - 1], l2 = l1 + k < n ? l1 + k : l1 + k - n;
			const size_t r1 = ind[i], r2 = r1 + k < n ? r1 + k : r1 + k - n;
			tmp[r1] = tmp[l1] + (wgt[l1] != wgt[r1] || wgt[l2] != wgt[r2]);
		}
		wgt.swap(tmp);
	}
	return std::move(ind);
}
std::vector<size_t> suffix_array(std::string str)
{
	str.push_back(std::numeric_limits<char>::min());
	std::vector<size_t> res(cyclic_array(str));
	res.erase(res.begin());
	return std::move(res);
}
