#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace SuffixArray {
	const size_t MAX = 256;
	size_t n, size;
	std::vector<size_t> result, group, cnt, tmp;

	inline void countingSort(const std::vector<size_t> &highRadix, const size_t t) {
		size_t len = 1;
		for (size_t i = 0; i < n; i++) cnt[group[i]]++;
		for (; len < size && cnt[len - 1] != n; len++) cnt[len] += cnt[len - 1];

		for (auto iter = highRadix.rbegin() + 1; iter != highRadix.rend(); iter++) result[--cnt[group[*iter]]] = *iter;
		std::fill_n(cnt.begin(), len, 0);

		auto &newGroup = tmp;
		newGroup[result[0]] = 1;
		for (size_t i = 1, grp = 1; i < n; i++) {
			auto &prev = result[i - 1], &now = result[i];
			if (group[prev] != group[now] || group[prev] == group[now] && group[prev + t] != group[now + t]) grp++;
			newGroup[now] = grp;
		}
		std::swap(newGroup, group);
	}

	inline void radixSort(const std::vector<size_t> &lowRadix, const size_t t) {
		auto &highRadix = tmp;
		size_t p = 0;
		for (size_t i = n - t; i < n; i++) highRadix[p++] = i;
		for (size_t i = 0; i < n; i++) if (lowRadix[i] >= t) highRadix[p++] = lowRadix[i] - t;
		countingSort(highRadix, t);
	}

	std::vector<size_t> &suffixArray(const std::string &str) {
		n = str.size();
		result.resize(n);

		group.resize(n);
		tmp.resize(n);
		group.emplace_back(0);
		tmp.emplace_back(0);

		size = std::max(MAX, n + 1);
		cnt.resize(size);
		std::fill(cnt.begin(), cnt.end(), 0);

		size_t len = 1;
		for (size_t i = 0; i < n; i++) cnt[group[i] = size_t(str[i])]++;
		for (; len < size && cnt[len - 1] != n; len++) cnt[len] += cnt[len - 1];
		for (size_t i = 0; i < n; i++) result[--cnt[group[i]]] = i;
		std::fill_n(cnt.begin(), len, 0);

		for (size_t t = 1; t < n; t *= 2) radixSort(result, t);

		return result;
	}
}