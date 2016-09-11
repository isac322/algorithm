#pragma once
#include <vector>
#include <algorithm>

/*
* https://en.wikipedia.org/wiki/Maximum_subarray_problem
*/
long long MaximumSubarraySum(std::vector<int> arr) {
	long long maxSum, here;
	maxSum = here = arr[0];
	for (auto i = arr.begin() + 1; i != arr.end(); i++) {
		here = std::max(here + *i, (long long) *i);
		maxSum = std::max(here, maxSum);
	}
	return maxSum;
}