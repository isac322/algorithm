#pragma once

#include <queue>
#include <limits>
#include <vector>
#include <cstddef>
#include <algorithm>

/**
 * https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
 * Also known as Edmonds–Karp algorithm, since this implementation uses BFS.
 * https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
 */
namespace EdmondsKarp {
	using namespace std;
	
	const size_t &INF = numeric_limits<size_t>::max();
	
	/**
	* Store backward link for restoring path from source to sink, which is used in a single Ford-Fulkerson iteration.
	*/
	vector<size_t> traceLink;
	
	/**
	 * This method does not use reference(declaring with &) on `flow` parameter. because it modifies original graph.
	 * If you're implementation allows modification of original flow, declare graph parameter as reference type.
	 *
	 * @param	graph	storing connected nodes (Adjacency list)
	 * @param	flow	flow amount of graph (Adjacency matrix)
	 * @param	source	source of network flow graph
	 * @param	sink	sink of networt flow graph
	 * @return	maximum flow of this graph
	 */
	size_t edmondsKarp(const vector<vector<size_t>> &graph, vector<vector<size_t>> flow, size_t source, size_t sink) {
		const size_t &V = graph.size();
		traceLink.resize(V);
		
		// return value.
		size_t totalFlow = 0;
		
		// Storing node numbers for use in BFS.
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
				
				for (size_t there : graph[here]) {
					// if here->there edge can flow.
					if (flow[here][there] > 0 && traceLink[there] == V) {
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
				amount = min(amount, flow[v][u]);
			}
			
			for (size_t u = sink; u != source; u = traceLink[u]) {
				size_t &v = traceLink[u];
				flow[v][u] -= amount;
				flow[u][v] += amount;
			}
			
			totalFlow += amount;
		}
		
		return totalFlow;
	}
}