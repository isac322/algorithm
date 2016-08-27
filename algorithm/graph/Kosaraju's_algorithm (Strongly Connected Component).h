#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>

namespace SCC {
	using namespace std;

	const vector<vector<size_t>> *map, *revMap;
	vector<size_t> parent, topological;
	vector<bool> visit;
	size_t n, current;

	size_t find(size_t p) {
		size_t &q = parent[p];
		if (p == q) return p;
		return q = find(q);
	}

	inline void merge(size_t p, size_t q) {
		p = find(p);
		q = find(q);
		parent[q] = p;
	}

	inline void init(const size_t len) {
		parent.resize(len);
		for (size_t i = 0; i < len; i++) parent[i] = i;
	}

	void topologicalSort(size_t idx) {
		if (visit[idx]) return;
		visit[idx] = true;

		for (auto v : map->at(idx)) topologicalSort(v);

		topological.emplace_back(idx);
	}

	void getSCC(size_t idx) {
		if (visit[idx]) return;
		visit[idx] = true;

		for (auto v : revMap->at(idx)) getSCC(v);
		merge(current, idx);
	}

	vector<size_t>& SCC(const vector<vector<size_t>> &m, const vector<vector<size_t>> &revM) {
		map = &m;
		revMap = &revM;
		n = m.size();
		init(n);

		topological.clear();
		visit.resize(n);

		fill(visit.begin(), visit.end(), false);
		for (size_t i = 0; i < n; i++) topologicalSort(i);

		fill(visit.begin(), visit.end(), false);
		for (auto i = topological.rbegin(); i != topological.rend(); i++) {
			current = *i;
			getSCC(*i);
		}
		for (size_t i = 0; i < n; i++) find(i);

		return parent;
	}
}