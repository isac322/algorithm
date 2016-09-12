/*
idea : http://blog.myungwoo.kr/57
*/

#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>

namespace SuffixArray_LCP {
	using namespace std;
	
	const size_t MAX = 256;
	size_t n, size;
	vector<size_t> result, group, cnt, tmp, lcp;

	inline void countingSort(const vector<size_t> &highRadix, const size_t t) {
		size_t len = 1;
		for (size_t i = 0; i < n; i++) cnt[group[i]]++;
		for (; len < size && cnt[len - 1] != n; len++) cnt[len] += cnt[len - 1];

		for (auto iter = highRadix.rbegin() + 1; iter != highRadix.rend(); iter++) result[--cnt[group[*iter]]] = *iter;
		fill_n(cnt.begin(), len, 0);

		auto &newGroup = tmp;
		newGroup[result[0]] = 1;
		for (size_t i = 1, grp = 1; i < n; i++) {
			auto &prev = result[i - 1], &now = result[i];
			if (group[prev] != group[now] || group[prev] == group[now] && group[prev + t] != group[now + t]) grp++;
			newGroup[now] = grp;
		}
		swap(newGroup, group);
	}

	inline void radixSort(const vector<size_t> &lowRadix, const size_t t) {
		auto &highRadix = tmp;
		size_t p = 0;
		for (size_t i = n - t; i < n; i++) highRadix[p++] = i;
		for (size_t i = 0; i < n; i++) if (lowRadix[i] >= t) highRadix[p++] = lowRadix[i] - t;
		countingSort(highRadix, t);
	}

	vector<size_t> &suffixArray(const string &str) {
		n = str.size();
		result.resize(n);

		group.resize(n);
		tmp.resize(n);
		group.emplace_back(0);
		tmp.emplace_back(0);

		size = max(MAX, n + 1);
		cnt.resize(size);
		fill(cnt.begin(), cnt.end(), 0);

		size_t len = 1;
		for (size_t i = 0; i < n; i++) cnt[group[i] = size_t(str[i])]++;
		for (; len < size && cnt[len - 1] != n; len++) cnt[len] += cnt[len - 1];
		for (size_t i = 0; i < n; i++) result[--cnt[group[i]]] = i;
		fill_n(cnt.begin(), len, 0);

		for (size_t t = 1; t < n; t *= 2) radixSort(result, t);

		return result;
	}

	vector<size_t> &LCP(const string S, const vector<size_t> &SA) {
		const size_t n = SA.size();
		lcp.resize(n);
		auto &rank = tmp;

		for (size_t i = 0; i < n; i++) rank[SA[i]] = i;

		size_t k = 0;
		for (size_t i = 0; i < n; i++) {
			if (rank[i] == 0) k = 0;
			else {
				size_t j = SA[rank[i] - 1];
				while (i + k < n && j + k < n && S[i + k] == S[j + k]) k++;
				lcp[rank[i]] = k;
				if (k > 0) k--;
			}
		}

		return lcp;
	}

	vector<size_t> &LCP(const string S) {
		return LCP(S, suffixArray(S));
	}
}