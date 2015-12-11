#pragma once
#include <string>
#include <vector>

namespace KMP {
	std::vector<int> failure;

	int genFailure(const std::string &pattern, int index) {
		int &p = failure[index];
		if (p != -1) return p;

		// p = f(i - 1)
		p = genFailure(pattern, index - 1);
		const char &target = pattern[index];

		while (pattern[p] != target) {
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

		failure.resize(len, -1);

		failure[0] = 0;

		genFailure(pattern, len - 1);
	}

	int KMP(const std::string &target, const std::string &pattern) {
		initFailure(pattern);

		const size_t &len = target.size(), &last = pattern.size();
		size_t index = 0;

		for (size_t i = 0; i < len; i++) {
			// 찾음
			if (index == last) return i - last;
			else if (target[i] == pattern[index]) index++;
			else if (index != 0) {
				if (failure[index - 1] == 0) {
					index = 0;
				}
				else {
					index = failure[index - 1] - 1;
				}
				i--;
			}
		}

		if (index == last) return len - last;
		else return -1;
	}
}

/*
abacaabaccabacabaa
abacab
*/