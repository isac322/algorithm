#pragma once
#include <unordered_map>
#include <string>

namespace BM {
	std::unordered_map<char, int> map;

	void initMap(const std::string &pattern) {
		map.clear();

		for (size_t i = 0; i < pattern.size(); i++) {
			map[pattern[i]] = i;
		}
	}

	// TODO
	int boyer_moore(const std::string &target, const std::string &pattern) {
		initMap(pattern);

		const size_t &t_len = target.size(), &p_len = pattern.size();
		size_t start = 0, t_index, p_index;

		t_index = p_index = p_len - 1;

		while (t_index < t_len) {
			if (p_index == -1) return start;

			if (target[t_index] != pattern[p_index]) {
				t_index = start + p_len;
				start++;

				char next = target[t_index];
				if (map.find(next) != map.end()) {
					p_index = map[next];
				}
				else {
					p_index = p_len - 1;
				}
			}
			else {
				p_index--;
				t_index--;
			}
		}

		if (p_index == -1) return start;
		else return -1;
	}
}

/*
abacaabaccabacabaa
abacab
*/