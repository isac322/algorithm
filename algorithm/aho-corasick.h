#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

/**
usage :
build() -> search()
*/
namespace AhoCorasick {
	std::vector<std::string> patterns;
	std::string target;

	struct Node {
		std::unordered_map<char, Node *> next;
		char ch;
		bool last = false;
		size_t index = 0;
		Node *failure, *output = nullptr;

		explicit Node(char ch = '\0') : ch(ch), failure(&root) {}

		static Node root;
	};
	Node Node::root;

	void build() {
		size_t i = 0;
		for (const auto &str : patterns) {
			Node *p = &Node::root;
			auto iter = str.begin();

			while (iter != str.end() && p->next.find(*iter) != p->next.end()) {
				p = p->next.find(*iter)->second;
				iter++;
			}

			for (; iter != str.end(); iter++) {
				auto *node = new Node(*iter);
				p->next[*iter] = node;
				p = node;
			}

			p->last = true;
			p->index = i++;
		}

		std::queue<Node *> que;
		que.emplace(&Node::root);

		while (!que.empty()) {
			auto *p = que.front();
			que.pop();

			for (auto q : p->next) {
				que.emplace(q.second);

				auto pf = p;
				while (pf != pf->failure) {
					pf = pf->failure;

					if (pf->next.find(q.first) != pf->next.end()) {
						q.second->failure = pf->next.find(q.first)->second;

						if (q.second->failure->last) {
							q.second->output = q.second->failure;
						}
						else {
							q.second->output = q.second->failure->output;
						}

						break;
					}
				}
			}
		}
	}

	std::vector<std::pair<size_t, size_t>> mached;

	/**
	return value (pair<size_t, size_t>) :
	first : target position
	second : mached pattern index
	*/
	std::vector<std::pair<size_t, size_t>> &search() {
		mached.clear();

		auto *p = &Node::root;

		const auto &length = target.size();
		for (auto i = 1; i <= length; i++) {
			const auto &c = target[i - 1];

			while (p != &Node::root && p->next.find(c) == p->next.end())	p = p->failure;

			if (p->next.find(c) != p->next.end()) {
				p = p->next.find(c)->second;

				if (p->last) mached.emplace_back(i - patterns[p->index].size(), p->index);
				auto *tmp = p->output;
				while (tmp != nullptr && (tmp->last || tmp->output != nullptr)) {
					mached.emplace_back(i - patterns[tmp->index].size(), tmp->index);
					tmp = tmp->output;
				}
			}
		}

		return mached;
	}
}