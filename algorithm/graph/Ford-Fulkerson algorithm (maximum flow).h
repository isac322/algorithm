#pragma once
#include <queue>
#include <limits>
#include <vector>
#include <cstddef>
#include <algorithm>

namespace FordFulkerson {
	using namespace std;

	const size_t &INF = numeric_limits<size_t>::max();

	/*
	* Store backward link for restoring path from source to sink, which is used in a single Ford-Fulkerson iteration.
	*/
	vector<size_t> traceLink;

	/*
	* https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
	* 
	* This method does not use reference(declaring with &) on `graph` parameter. because it modifies original graph.
	* If you're implementation allows modification of original graph, declare graph parameter as reference type.
	*
	* @param graph Adjacency matrix
	* @param source source of network flow graph
	* @param sink sink of networt flow graph
	*/
	size_t fordFulkerson(vector<vector<size_t>> graph, size_t source, size_t sink) {
		const size_t &V = graph.size();
		traceLink.resize(V);

		// return value.
		size_t totalFlow = 0;

		/*
		* Storing node numbers for use in BFS.
		*/
		deque<size_t> que;

		/*
		* Iterate until there's no more path from source to sink.
		*/
		while (true) {
			que.clear();
			fill(traceLink.begin(), traceLink.end(), V);
			
			// BFS start with source.
			que.emplace_back(source);

			while (!que.empty()) {
				size_t here = que.front();
				if (here == sink) break;
				que.pop_front();

				for (size_t there = 0; there < V; there++) {
					// if here->there edge can flow.
					if (graph[here][there] > 0 && traceLink[there] == V) {
						que.emplace_back(there);
						traceLink[there] = here;
					}
				}
			}

			// true if no more path.
			if (traceLink[sink] == V) break;

			size_t amount = INF;
			// Find lowest flow amount within backward path that starting from sink.
			for (size_t u = sink; u != source; u = traceLink[u]) {
				size_t &v = traceLink[u];
				amount = min(amount, graph[v][u]);
			}

			for (size_t u = sink; u != source; u = traceLink[u]) {
				size_t &v = traceLink[u];
				graph[v][u] -= amount;
				graph[u][v] += amount;
			}

			totalFlow += amount;
		}

		return totalFlow;
	}
}