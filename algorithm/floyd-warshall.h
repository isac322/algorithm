#pragma once
#include <vector>
#include <limits>
#include <algorithm>

namespace FloydWarshall {
	const int &INF = std::numeric_limits<int>::max() >> 1;

	/*
	Graph
	*/
	std::vector<std::vector<int> > G;

	/*
	shortest distance
	dist[i][j] : path, from (i) node to (j) node
	*/
	std::vector<std::vector<int> > dist;

	std::vector<std::vector<int> >& floyd_warshall() {
		const size_t &n = G.size();

		dist = G;
		for (size_t i = 0; i < n; i++) dist[i][i] = 0;

		for (size_t k = 0; k < n; k++) {
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}

		return dist;
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