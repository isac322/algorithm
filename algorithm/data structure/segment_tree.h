#pragma once

#include <vector>
#include <cstddef>

using namespace std;

/**
 * https://en.wikipedia.org/wiki/Segment_tree
 *
 * indexing : 0...n-1
 * 
 * range update support
 * 
 * sum of 5 element from first element : query(0, 4)
 * range add V from i to j : updateRange(i, j, V)
 */
template<typename T, typename N = T>
struct SegmentTree {
	vector<T> tree;
	size_t size, range, left, right, index;
	N value;
	
	void update(const size_t begin, const size_t end, const size_t node) {
		if (index < begin || end < index) return;
		else {
			tree[node] += value;
			const size_t mid = (begin + end) >> 1;
			update(begin, mid, node * 2);
			update(mid + 1, end, node * 2 + 1);
		}
	}
	
	void update(const size_t index, const N value) {
		this->index = index;
		this->value = value;
		
		update(0, range - 1, 1);
	}
	
	T _updateRange(const size_t begin, const size_t end, const size_t node) {
		if (left > end || right < begin) return tree[node];
		else {
			if (begin == end) return tree[node] += value;
			
			const size_t mid = (begin + end) >> 1;
			return tree[node] = _updateRange(begin, mid, node * 2) + _updateRange(mid + 1, end, node * 2 + 1);
		}
	}
	
	void updateRange(size_t left, size_t right, const N value) {
		if (left > right) swap(left, right);
		this->left = left;
		this->right = right;
		this->value = value;
		
		_updateRange(0, range - 1, 1);
	}
	
	T query(const size_t begin, const size_t end, const size_t node) {
		if (left > end || right < begin) return 0;
		else if (left <= begin && end <= right) return tree[node];
		else {
			const size_t mid = (begin + end) >> 1;
			return query(begin, mid, node * 2) + query(mid + 1, end, node * 2 + 1);
		}
	}
	
	T query(size_t left, size_t right) {
		if (left > right) swap(left, right);
		this->left = left;
		this->right = right;
		
		return query(0, range - 1, 1);
	}
	
	T init(const vector<N> &arr, const size_t left, const size_t right, const size_t node) {
		if (left == right) return tree[node] = arr[left];
		else {
			const size_t mid = (left + right) >> 1;
			return tree[node] = init(arr, left, mid, node * 2) + init(arr, mid + 1, right, node * 2 + 1);
		}
	}
	
	SegmentTree(const vector<N> &arr) {
		size_t cnt = 0;
		
		range = arr.size();
		for (size_t s = range; s != 0; s >>= 1) cnt++;
		if (range << 1 != size_t(1) << cnt) cnt++;
		
		size = (1 << cnt) + 1;
		tree.resize(size);
		
		init(arr, 0, range - 1, 1);
	}
};