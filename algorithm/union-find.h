#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>

struct UnionFind {
	std::vector<std::size_t> parent, depth;

	UnionFind(std::size_t len) :parent(len), depth(len, 1) {
		for (std::size_t i = 0; i < len; i++) parent[i] = i;
	}

	std::size_t find(std::size_t n) {
		std::size_t &p = parent[n];
		if (p == n) return n;
		else return p = find(p);
	}

	void uni(std::size_t p, std::size_t q) {
		p = find(p);
		q = find(q);
		if (p == q) return;
		else if (depth[p] > depth[q]) parent[q] = p;
		else if (depth[p] != depth[q]) parent[p] = q;
		else parent[q] = p, depth[p]++;
	}
};