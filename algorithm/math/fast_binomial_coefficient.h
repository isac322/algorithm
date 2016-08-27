/**
* http://blog.plover.com/math/choose.html
* calculate a single binomial coefficient.
*
* Time : O(k)
* Space : O(1)
*/
#pragma once
#include <algorithm>

namespace FastBinomial {
	using namespace std;

	long long binomial(long long n, long long k) {
		k = min(k, n - k);
		long long r, v;
		r = v = 1;
		for (; r <= k; r++) v = v*(n - r + 1) / r;
		return v;
	}
}