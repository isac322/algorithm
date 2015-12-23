#pragma once
#include <unordered_map>
#include <string>
#include <vector>

namespace BoyerMoore {
	std::unordered_map<char, size_t> map;
	std::vector<size_t> mached;

	void init_map(const std::string &pattern) {
		map.clear();

		for (size_t i = 0; i < pattern.size(); i++) {
			map[pattern[i]] = i;
		}
	}
	
	int boyer_moore(const std::string &target, const std::string &pattern) {
		init_map(pattern);

		const size_t &t_len = target.size(), &p_len = pattern.size();
		size_t index = p_len;

		bool check;

		while (true) {
			check = true;

			for (size_t i = 1; i <= p_len; i++) {
				if (target[index - i] != pattern[p_len - i]) {
					check = false;
					break;
				}
			}

			if (check) {
				return index - p_len;
			}
			else if (index >= t_len) {
				return -1;
			}
			else {
				index += p_len - map[target[index]];
			}
		}
	}

	std::vector<size_t>& boyer_moore_all(const std::string &target, const std::string &pattern) {
		init_map(pattern);
		mached.clear();

		const size_t &t_len = target.size(), &p_len = pattern.size();
		size_t index = p_len;

		bool check;

		while (true) {
			check = true;

			for (size_t i = 1; i <= p_len; i++) {
				if (target[index - i] != pattern[p_len - i]) {
					check = false;
					break;
				}
			}

			if (check) {
				mached.push_back(index - p_len);

				index += p_len - map[target[index]];
			}
			else if (index >= t_len) {
				return mached;
			}
			else {
				index += p_len - map[target[index]];
			}
		}
	}
}

/*
abacaabaccabacabaa
abacab
*/