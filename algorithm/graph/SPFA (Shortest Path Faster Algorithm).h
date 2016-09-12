#pragma once
#include <queue>
#include <limits>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>

/**
 * find shortest path on graph even if it contains negative weighted edge.
 *
 * If graph contains negative weighted edge, SPFA is faster than bellman-ford in average case.
 * https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm
 */
namespace SPFA {
	using namespace std;

	const int INF = numeric_limits<int>::max();

	deque<size_t> que;
	vector<bool> isInQ;

	// shortest distance from start node.
	vector<int> dist;

	// count how many times are visited on a node.
	vector<size_t> visits;

	// node number
	size_t n;

	/**
	 * @param	graph	(weight, next node number) paired graph (Adjacency list)
	 * @param	start	start node number
	 * @return	distance vector that starts from start. if graph contains negative cycle, returns empty vector.
	 */
	vector<int>& spfa(const vector<vector<pair<int, size_t>>> &graph, size_t start) {
		n = graph.size();

		// initialize
		que.clear();
		dist.resize(n);
		isInQ.resize(n, false);
		visits.resize(n);
		fill(dist.begin(), dist.end(), INF);
		fill(visits.begin(), visits.end(), 0);

		dist[start] = 0;
		isInQ[start] = true;
		que.emplace_back(start);

		// looping until all nodes become relaxed.
		while (!que.empty()) {
			size_t here = que.front();
			que.pop_front();
			isInQ[here] = false;

			visits[here]++;
			/*
			* Incapacitate negative cycle
			* http://stackoverflow.com/a/26771298/6821103
			*/
			if (visits[here] == n) {
				dist.clear();
				return dist;
			}

			for (auto edge : graph[here]) {
				size_t next = edge.second;
				int weight = edge.first;

				if (dist[next] > dist[here] + weight) {
					dist[next] = dist[here] + weight;
					
					// push to queue only if queue doesn't have `next`.
					if (isInQ[next] == false) {
						que.emplace_back(next);
						isInQ[next] = true;
					}
				}
			}
		}

		return dist;
	}

	int spfa(const vector<vector<pair<int, size_t>>> &graph, size_t start, size_t end) {
		return spfa(graph, start)[end];
	}

	/**
	 * find negative cycle by conducting one more phase on `bellman_ford()`.
	 * http://stackoverflow.com/a/26771298/6821103
	 *
	 * must call after "bellman_ford(start)" for all weakly component on graph `graph`.
	 *
	 * @return	true there is negative cycle.
	 */
	bool hasNegativCycle() {
		for (auto v : visits) if (v == n) return true;
		return false;
	}
}