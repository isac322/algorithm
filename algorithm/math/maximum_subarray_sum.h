#pragma once
#include <vector>
#include <algorithm>

int MaximumSubarraySum(std::vector<int> arr) {
	long long maxSum, here;
	maxSum = here = arr[0];
	for (auto i = arr.begin() + 1; i != arr.end(); i++) {
		here = std::max(here + *i, (long long) *i);
		maxSum = std::max(here, maxSum);
	}
	return maxSum;
}