#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>

namespace SCC {
	using namespace std;
	
	const vector<vector<size_t>> *map, *revMap;
	vector<size_t> SCCId, topological;
	vector<bool> visit;
	size_t n, current;
	
	void topologicalSort(size_t idx) {
		if (visit[idx]) return;
		visit[idx] = true;
		
		for (auto v : map->at(idx)) topologicalSort(v);
		
		topological.emplace_back(idx);
	}
	
	void makeSCC(size_t idx) {
		/*
		 * because `visit`'s all element are converted to `true` in `topologicalSort`,
		 * `visit` can use as an inverted state.
		 */
		if (!visit[idx]) return;
		visit[idx] = false;
		
		for (auto v : revMap->at(idx)) makeSCC(v);
		SCCId[idx] = current;
	}
	
	vector<size_t> &SCC(const vector<vector<size_t>> &m, const vector<vector<size_t>> &revM) {
		map = &m;
		revMap = &revM;
		n = m.size();
		
		topological.clear();
		visit.resize(n);
		SCCId.resize(n);
		
		fill(visit.begin(), visit.end(), false);
		for (size_t i = 0; i < n; i++) topologicalSort(i);
		
		for (auto i = topological.rbegin(); i != topological.rend(); i++) {
			current = *i;
			makeSCC(*i);
		}
		
		return SCCId;
	}
}