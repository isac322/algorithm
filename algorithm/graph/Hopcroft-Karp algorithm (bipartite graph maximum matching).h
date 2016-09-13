#pragma once

#include <queue>
#include <limits>
#include <vector>
#include <cstddef>
#include <algorithm>

/**
 * Finds maximized matching on bipartite graph.
 * Detailed description:
 * https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm
 *
 * All indexes of graph must start from 1.
 */
namespace HopcroftKarp {
	using namespace std;

	const size_t &INF = numeric_limits<size_t>::max();
	const size_t &NIL = 0;

	vector<size_t> pairL, pairR, level;
	queue<size_t> que;
	const vector<vector<size_t>> *graph;
	size_t n, totalMatching;


	/**
	 * Find augmenting path that starts from free vertex and ends with free vertex.
	 * (See the link above to detail terminology)
	 *
	 * @return	true if can find augmenting path within graph
	 */
	inline bool bfs() {
		// Have to start from free vertex. so mark nonfree vertex as infinite level on `level` array.
		for (size_t left = 1; left <= n; left++) {
			if (pairL[left] == NIL) {
				level[left] = 0;
				que.emplace(left);
			}
			else level[left] = INF;
		}
		level[NIL] = INF;

		
		// starting from free vertices, keep spreads out until to find another free vertices.
		while (que.size()) {
			size_t left = que.front();
			que.pop();

			if (level[left] >= level[NIL]) continue;

			for (size_t right : graph->at(left)) {
				size_t prevPair = pairR[right];

				if (level[prevPair] == INF) {
					level[prevPair] = level[left] + 1;
					que.emplace(prevPair);
				}
			}
		}

		return level[NIL] != INF;
	}

	bool dfs(size_t left) {
		if (left == NIL) return true;

		for (size_t right : graph->at(left)) {
			size_t &traceLink = pairR[right];

			if (level[traceLink] == level[left] + 1 && dfs(traceLink)) {
				traceLink = left;
				pairL[left] = right;
				return true;
			}
		}

		level[left] = INF;
		return false;
	}

	size_t maximumMatching(const vector<vector<size_t>> &graph, size_t n, size_t m) {
		HopcroftKarp::graph = &graph;
		HopcroftKarp::n = n;

		level.resize(n + 1);
		pairL.resize(n + 1);
		fill(pairL.begin(), pairL.end(), NIL);
		pairR.resize(m + 1);
		fill(pairR.begin(), pairR.end(), NIL);
		totalMatching = 0;

		while (bfs()) {
			for (size_t left = 1; left <= n; left++) {
				if (pairL[left] == NIL && dfs(left)) {
					totalMatching++;
				}
			}
		}

		return totalMatching;
	}
}