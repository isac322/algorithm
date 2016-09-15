#pragma once

#include <vector>
#include <limits>
#include <cstddef>
#include <algorithm>

using namespace std;

/**
 * https://en.wikipedia.org/wiki/Range_minimum_query
 */
template <class T>
class RMQ {
private:
	vector<T> tree;
	const vector<T> *arr;
	size_t left, right, size;
	T INF;

	T init(size_t node, size_t left, size_t right) {
		if (left == right) return tree[node] = arr->at(left);

		size_t mid = (right + left) >> 1;
		return tree[node] = min(init(node * 2 + 1, left, mid), init(node * 2 + 2, mid + 1, right));
	}

	T query(size_t node, size_t start, size_t end) {
		if (right < start || end < left) return INF;
		else if (left <= start && end <= right) return tree[node];

		size_t mid = (start + end) >> 1;
		return min(query(node * 2 + 1, start, mid), query(node * 2 + 2, mid + 1, end));
	}

public:
	RMQ(const vector<T> &arr) {
		this->arr = &arr;
		this->size = arr.size();

		INF = numeric_limits<T>::max();
		size_t cnt = 0;
		for (size_t s = size; s != 0; s >>= 1) cnt++;
		if (size << 1 != size_t(1) << cnt) cnt++;

		tree.resize(size_t(1) << cnt);

		init(0, 0, arr.size() - 1);
	}

	/**
	 * Usage (minimum value of 1st ~ 5th):
	 * query(0, 4);
	 *
	 * @param	left	first index of range (indexing is always starts with 0)
	 * @param	right	last index of range (indexing is always starts with 0)
	 */
	T query(size_t left, size_t right) {
		this->left = left;
		this->right = right;
		return query(0, 0, size - 1);
	}
};