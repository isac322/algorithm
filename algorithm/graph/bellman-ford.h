#pragma once

#include <vector>
#include <limits>
#include <cstddef>
#include <algorithm>

/*
* find shortest path on graph even if it contains negative weighted edge.
*
* https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm#Algorithm
*
* Showing visually on web:
* http://visualgo.net/sssp
*/
namespace BellmanFord {
	using namespace std;

	typedef pair<int, int> PAIR;

	const int &INF = numeric_limits<int>::max();

	/*
	* Graph (Adjacency list)
	* pair.first : weight
	* pair.second : destination node
	*/
	vector<vector<PAIR>> G;

	/*
	* shortest distance from start node.
	*/
	vector<int> dist;

	/*
	* @param	start	start node number (starting from 0)
	* @return	shortest distance vector that starting from `start` node
	*/
	vector<int>& bellman_ford(int start) {
		const size_t &n = G.size();

		dist.resize(n);
		fill(dist.begin(), dist.end(), INF);
		dist[start] = 0;

		for (size_t i = 0; i < n - 1; i++) {
			for (size_t here = 0; here < n; here++) {
				if (dist[here] != INF) {
					for (auto &j : G[here]) {
						int there = j.second;
						int weight = j.first;

						dist[there] = min(dist[there], dist[here] + weight);
					}
				}
			}
		}

		return dist;
	}

	int bellman_ford(int start, int end) {
		return bellman_ford(start)[end];
	}

	/*
	* find negative cycle by conducting one more phase on `bellman_ford()`.
	* https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm#Finding_negative_cycles
	*
	* must call after "bellman_ford(start)" for all weakly component on graph `G`.
	*
	* @return	true there is negative cycle.
	*/
	bool hasNegativCycle() {
		const size_t &n = G.size();

		for (size_t here = 0; here < n; here++) {
			if (dist[here] != INF) {
				for (auto &j : G[here]) {
					const int &there = j.second;
					const int &weight = j.first;

					if (dist[there] > dist[here] + weight) {
						return true;
					}
				}
			}
		}

		return false;
	}
}

/*
6 19
0 1 3
1 0 3
0 2 5
2 0 5
1 2 -3
1 3 4
3 1 4
1 4 7
4 1 7
2 3 2
3 2 2
2 4 6
4 2 6
3 4 2
4 3 2
3 5 2
5 3 2
4 5 5
5 4 5
*/