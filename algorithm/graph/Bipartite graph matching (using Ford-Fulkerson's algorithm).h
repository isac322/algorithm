#pragma once
#include <vector>
#include <cstddef>
#include <algorithm>

/*
* find maximum matching on bipartite graph.
* basic explanation:
* http://www.geeksforgeeks.org/maximum-bipartite-matching/
*
* Unlike link, this method uses adjacency list instead of adjacency matrix.
* and it assume that left and right part have same number of nodes.
*/
namespace BipartiteMatching {
	using namespace std;

	const vector<vector<size_t>> *g;
	vector<size_t> matchLink;
	vector<bool> visit;
	size_t n;

	bool dfs(size_t node) {
		if (visit[node]) return false;
		visit[node] = true;

		for (auto next : g->at(node)) {
			if (matchLink[next] == n || dfs(matchLink[next])) {
				matchLink[next] = node;
				return true;
			}
		}

		return false;
	}

	size_t maximumMatching(const vector<vector<size_t>> &graph) {
		g = &graph;
		n = graph.size();

		visit.resize(n);
		matchLink.resize(n);
		fill(matchLink.begin(), matchLink.end(), n);

		size_t cnt = 0;
		for (size_t i = 0; i < n; i++) {
			fill(visit.begin(), visit.end(), false);
			if (dfs(i)) cnt++;
		}

		return cnt;
	}
}