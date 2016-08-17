/**
* Check whether a given graph is Bipartite or not.
* Even if the given graph isn't single connected component graph.
* The given graph must be Adjacency List.

Test bipartite graph with DFS
*/
#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>

namespace BipartiteTester {
	using namespace std;
	const vector<vector<size_t>> *map;
	vector<bool> visit, color;

	bool dfs(size_t index, bool isRed) {
		if (visit[index]) return true;
		visit[index] = true;

		color[index] = isRed;
		for (auto v : map->operator[](index)) {
			if (!dfs(v, !isRed)) return false;
			if (color[v] == color[index]) return false;
		}

		return true;
	}

	bool bipartiteTest(const vector<vector<size_t>> &m) {
		map = &m;

		const size_t &len = m.size();
		visit.resize(len);
		fill(visit.begin(), visit.end(), false);
		color.resize(len);
		fill(color.begin(), color.end(), false);

		for (size_t i = 0; i < len; i++) if (!dfs(i, false)) return false;
		return true;
	}
}