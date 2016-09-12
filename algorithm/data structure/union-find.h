#pragma once

#include <vector>
#include <cstddef>

using namespace std;

/**
 * Disjoint-set
 *
 * https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 */
struct UnionFind {
	vector<size_t> parent, depth, size;
	
	/**
	 * @param	len	set size
	 */
	UnionFind(size_t len) : parent(len), depth(len, 1), size(len, 1) {
		for (size_t i = 0; i < len; i++) parent[i] = i;
	}
	
	/**
	 * find top parent of given n.
	 * and compress set by removing intermediate path.
	 *
	 * @param	n	node number
	 * @return	top parent of node n
	 */
	size_t find(size_t n) {
		size_t &p = parent[n];
		if (p == n) return n;
		else return p = find(p);
	}
	
	size_t merge(size_t p, size_t q) {
		p = find(p);
		q = find(q);
		if (p == q) return size[p];
		else if (depth[p] > depth[q]) {
			parent[q] = p;
			return size[p] += size[q];
		}
		else if (depth[p] != depth[q]) {
			parent[p] = q;
			return size[q] += size[p];
		}
		else {
			parent[q] = p, depth[p]++;
			return size[p] += size[q];
		}
	}
};