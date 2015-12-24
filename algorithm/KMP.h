#pragma once

#include <string>
#include <vector>
#include <limits>

namespace KMP {
	const size_t &INF = std::numeric_limits<size_t>::max();

	std::vector<size_t> failure;
	std::vector<size_t> mached;

	size_t genFailure(const std::string &pattern, size_t index) {
		if (index == 0) return 0;
		size_t &p = failure[index - 1];
		if (p != INF) return p;

		// p = f(i - 1)
		p = genFailure(pattern, index - 1);

		while (pattern[p] != pattern[index - 1]) {
			// 더이상 매칭 불가능
			if (p == 0) {
				return p = 0;
			}

			// p = f(f(...f(i - 1)...))
			p = genFailure(pattern, p);
		}

		return p += 1;
	}

	void initFailure(const std::string &pattern) {
		const size_t &len = pattern.size();

		failure.resize(len);
		fill(failure.begin(), failure.end(), INF);

		failure[0] = 0;

		genFailure(pattern, len);
	}

	size_t KMP(const std::string &target, const std::string &pattern) {
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

	std::vector<size_t> &KMP_all(const std::string &target, const std::string &pattern) {
		initFailure(pattern);
		mached.clear();

		const size_t &len = target.size(), &last = pattern.size();
		size_t index = 0;

		for (size_t i = 0; i < len; i++) {
			if (target[i] == pattern[index]) {
				index++;

				if (index == last) {
					mached.emplace_back(i - index + 1);

					index = failure.back();
				}
			}
			else if (index != 0) {
				index = failure[index - 1];

				i--;
			}
		}

		return mached;
	}
}

/*
abacaabaccabacabaa
abacab
*/