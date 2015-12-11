#pragma once
#include <vector>
#include <functional>
#include <queue>
#include <limits>

namespace dijkstra {
	typedef std::pair<int, int> PAIR;

	const int &INF = std::numeric_limits<int>::max();

	/*
	Graph
	pair.first : weight
	pair.second : destination node
	*/
	std::vector<std::vector<PAIR> > G;

	/*
	shortest distance from start node
	*/
	std::vector<int> dist;

	std::vector<int>& dijkstra(int start, int end, bool allPath = false) {
		const size_t &n = G.size();

		dist.resize(n, INF);
		std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR> > que;

		dist[start] = 0;
		que.push(std::make_pair(0, start));

		while (!que.empty()) {
			PAIR t = que.top();
			que.pop();

			int here = t.second;
			int d = t.first;

			if (here == end && !allPath) break;

			for (std::vector<PAIR>::iterator i = G[here].begin(); i != G[here].end(); i++) {
				const int &there = i->second;
				const int &weight = i->first;

				if (dist[there] > d + weight) {
					dist[there] = d + weight;

					que.push(std::make_pair(dist[there], there));
				}
			}
		}

		return dist;
	}
}


/*
6 10
0 1 3
0 2 5
1 2 3
1 3 4
1 4 7
2 3 2
2 4 6
3 4 2
3 5 2
4 5 5
*/