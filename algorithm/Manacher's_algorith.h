/**
* Find all odd-length palindrome in a given string.
*
* idea : http://blog.myungwoo.kr/56
*/
#pragma once
#include <cstddef>
#include <string>
#include <algorithm>

namespace Manacher {
	using namespace std;

	size_t *arr = nullptr;

	size_t* findAllPalindrome(const string &str) {
		size_t r = 0, p = 0;
		const size_t &len = str.size();

		arr = new size_t[len];
		for (size_t i = 0; i < len; i++) {
			if (r >= i) arr[i] = min(r - i, arr[2 * p - i]);
			else arr[i] = 0;

			while (i - arr[i] > 0 && i + arr[i] < len && str[i - arr[i]] == str[i + arr[i]]) arr[i]++;
			if (r < i + arr[i]) {
				r = i + arr[i];
				p = i;
			}
		}
		return arr;
	}
}