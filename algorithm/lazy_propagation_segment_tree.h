/*
indexing : 0...n-1

lazy range update support
(faster than default segment tree in range update)

sum of 5 element from first element : query(0, 4)
range add V from i to j : updateRange(i, j, V)
*/

#pragma once

#include <vector>

template <typename T, typename N = T>
struct LazySegmentTree {
	std::vector<T> tree;
	std::vector<N> lazy;
	size_t range, left, right;
	N value;
	
	inline void lazyUpdate(const size_t begin, const size_t end, const size_t node) {
		tree[node] += lazy[node] * (end - begin + 1);
		if (begin != end) {
			lazy[node * 2 + 1] += lazy[node];
			lazy[node * 2 + 2] += lazy[node];
		}
		lazy[node] = 0;
	}

	T _updateRange(const size_t begin, const size_t end, const size_t node) {
		lazyUpdate(begin, end, node);

		if (right < begin || end < left) return tree[node];
		else if (begin == end) return tree[node] += value;
		else if (left <= begin && end <= right) {
			lazy[node * 2 + 1] += value;
			lazy[node * 2 + 2] += value;
			return tree[node] += (end - begin + 1)*value;
		}
		else {
			const size_t mid = (begin + end) >> 1;
			return tree[node] = _updateRange(begin, mid, node * 2 + 1) + _updateRange(mid + 1, end, node * 2 + 2);
		}
	}

	void updateRange(size_t left, size_t right, const N value) {
		if (left > right) std::swap(left, right);
		this->left = left;
		this->right = right;
		this->value = value;

		_updateRange(0, range - 1, 0);
	}

	T query(const size_t begin, const size_t end, const size_t node) {
		lazyUpdate(begin, end, node);

		if (right < begin || end < left) return 0;
		else if (begin == end) return tree[node];
		else if (left <= begin && end <= right) return tree[node];
		else {
			const size_t mid = (begin + end) >> 1;
			return query(begin, mid, node * 2 + 1) + query(mid + 1, end, node * 2 + 2);
		}
	}

	T query(size_t left, size_t right) {
		if (left > right) std::swap(left, right);
		this->left = left;
		this->right = right;

		return query(0, range - 1, 0);
	}

	T init(const std::vector<N> &arr, const size_t left, const size_t right, const size_t node) {
		if (left == right) return tree[node] = arr[left];
		else {
			const size_t mid = (left + right) >> 1;
			return tree[node] = init(arr, left, mid, node * 2 + 1) + init(arr, mid + 1, right, node * 2 + 2);
		}
	}

	LazySegmentTree(const std::vector<N> &arr) {
		size_t size = 1;
		range = arr.size();
		for (size_t s = range; s != 0; s >>= 1) size <<= 1;
		if (range << 1 != size) size <<= 1;

		tree.resize(size);
		lazy.resize(size);
		fill(lazy.begin(), lazy.end(), 0);

		init(arr, 0, range - 1, 0);
	}
};