#pragma once

#include <string>
#include <vector>
#include <limits>
#include <cstddef>

namespace KMP {
	using namespace std;
	
	const size_t &INF = numeric_limits<size_t>::max();

	vector<size_t> failure;
	vector<size_t> matched;

	size_t genFailureOnline(const string &pattern, size_t index) {
		if (index == 0) return 0;
		size_t &p = failure[index - 1];
		if (p != INF) return p;

		// p = f(i - 1)
		p = genFailureOnline(pattern, index - 1);

		while (pattern[p] != pattern[index - 1]) {
			// 더이상 매칭 불가능
			if (p == 0) {
				return p = 0;
			}

			// p = f(f(...f(i - 1)...))
			p = genFailureOnline(pattern, p);
		}

		return p += 1;
	}

	void initFailureOnline(const string &pattern) {
		const size_t &len = pattern.size();

		failure.resize(len);
		fill(failure.begin(), failure.end(), INF);

		failure[0] = 0;

		genFailureOnline(pattern, len);
	}

	void initFailure(const string &pattern) {
		const size_t &len = pattern.size();

		failure.resize(len);
		fill(failure.begin(), failure.end(), 0);

		size_t index = 0;
		for (size_t i = 1; i < len; i++) {
			if (pattern[i] == pattern[index]) {
				failure[i] = ++index;
			}
			else if (index != 0) {
				index = failure[index - 1];

				i--;
			}
		}
	}

	size_t KMP(const string &target, const string &pattern) {
		initFailure(pattern);

		const size_t &len = target.size(), &last = pattern.size();
		size_t index = 0;

		for (size_t i = 0; i < len; i++) {
			if (target[i] == pattern[index]) {
				index++;

				if (index == last) return i - last + 1;
			}
			else if (index != 0) {
				index = failure[index - 1];

				i--;
			}
		}

		return len;
	}

	vector<size_t> &KMP_all(const string &target, const string &pattern) {
		initFailure(pattern);
		matched.clear();

		const size_t &len = target.size(), &last = pattern.size();
		size_t index = 0;

		for (size_t i = 0; i < len; i++) {
			if (target[i] == pattern[index]) {
				index++;

				if (index == last) {
					matched.emplace_back(i - index + 1);

					index = failure.back();
				}
			}
			else if (index != 0) {
				index = failure[index - 1];

				i--;
			}
		}

		return matched;
	}
}

/*
abacaabaccabacabaa
abacab
*/