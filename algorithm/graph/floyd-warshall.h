#pragma once

#include <vector>
#include <limits>
#include <cstddef>
#include <algorithm>

namespace FloydWarshall {
	using namespace std;
	
	const int &INF = numeric_limits<int>::max();
	
	/*
	Graph
	G[i][j] : (i)->(j) edge weight
	if not exist INF
	*/
	vector<vector<int>> G;
	
	/*
	shortest distance
	dist[i][j] : (i) node to (j) node
	*/
	vector<vector<int>> dist;
	
	void init(int n) {
		G.resize(n, vector<int>(n, INF));
		for (size_t i = 0; i < n; i++) G[i][i] = 0;
	}
	
	vector<vector<int>> &floydWarshall() {
		const size_t &n = G.size();
		
		dist = G;
		
		for (size_t k = 0; k < n; k++) {
			for (size_t i = 0; i < n; i++) {
				if (dist[i][k] != INF) {
					for (size_t j = 0; j < n; j++) {
						if (dist[k][j] != INF) {
							dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
						}
					}
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