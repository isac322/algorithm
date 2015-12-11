#pragma once
#include <vector>
#include <limits>
#include <algorithm>

namespace BF {
	typedef std::pair<int, int> PAIR;

	const int &INF = std::numeric_limits<int>::max();

	/*
	graph
	pair.first : weight
	pair.second : destination node
	*/
	std::vector<std::vector<PAIR> > G;

	std::vector<int> dist;

	std::vector<int>& bellman_ford(int start) {
		const size_t &n = G.size();

		dist.resize(n, INF);
		dist[start] = 0;

		for (size_t i = 0; i < n - 1; i++) {
			for (size_t here = 0; here < n; here++) {
				if (dist[here] != INF) {
					for (std::vector<PAIR>::iterator j = G[here].begin(); j != G[here].end(); j++) {
						const int &there = j->second;
						const int &weight = j->first;

						dist[there] = std::min(dist[there], dist[here] + weight);
					}
				}
			}
		}

		return dist;
	}

	int bellman_ford(int start, int end) {
		return bellman_ford(start)[end];
	}

	bool hasNegativCycle() {
		const size_t &n = G.size();

		for (size_t here = 0; here < n; here++) {
			if (dist[here] != INF) {
				for (std::vector<PAIR>::iterator j = G[here].begin(); j != G[here].end(); j++) {
					const int &there = j->second;
					const int &weight = j->first;

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