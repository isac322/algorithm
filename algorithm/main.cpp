#include "KMP.h"
#include "boyer-moore.h"
#include "prim.h"
#include "dijkstra.h"
#include "bellman-ford.h"
#include "floyd-warshall.h"
#include "convex_hull.h"
#include "aho-corasick.h"
#include "suffix_array_lcp.h"
#include "lazy_propagation_segment_tree.h"
#include "extended_euclidean.h"
#include "online_palindrome_check.h"
#include "bipartite_graph_tester.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;


void primTest() {
	int n, t;
	cin >> n >> t;

	prim::G.resize(n);
	for (int i = 0; i < t; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		prim::G[a].emplace_back(c, b);
	}

	auto re = prim::prim();

	for (auto i = 0; i < re.size(); i++) {
		for (auto &t : re[i]) {
			printf("(%d -> %d) ", i, t.second);
		}
	}
}

void bellmanTest() {
	int n, t;
	cin >> n >> t;

	BellmanFord::G.resize(n);
	for (int i = 0; i < t; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		BellmanFord::G[a].emplace_back(c, b);
	}

	auto re = BellmanFord::bellman_ford(0);

	for (auto d : re) {
		printf("%d ", d);
	}

	printf("\n%d", BellmanFord::hasNegativCycle() ? 1 : 0);
}

void boyerMooreTest() {
	string t, p;

	cin >> t >> p;

	printf("%zd\n", BoyerMoore::boyer_moore(t, p));

	for (auto &c : BoyerMoore::boyer_moore_all(t, p)) {
		printf("%zd ", c);
	}
}

void KMPTest() {
	string t, p;

	cin >> t >> p;

	printf("%zd", KMP::KMP(t, p));

	puts("");
	for (auto t : KMP::failure) {
		printf("%zd ", t);
	}
}

void ahoCorasickTest() {
	int n;
	cin >> n;

	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		AhoCorasick::patterns.emplace_back(str);
	}

	cin >> AhoCorasick::target;

	AhoCorasick::build();

	for (const auto t : AhoCorasick::search()) {
		cout << "at " << t.first << ", pattern \"" << AhoCorasick::patterns[t.second] << "\" found\n";
	}
}

void suffixArrayTest() {
	string t;
	getline(cin, t);

	for (size_t p : SuffixArray_LCP::suffixArray(t)) {
		cout << t.substr(p) << '\n';
	}
}

void segmentTreeTest() {
	size_t n, t;
	cin >> t;
	vector<size_t> arr;

	for (size_t i = 0; i < t; i++) {
		cin >> n;
		arr.emplace_back(n);
	}

	LazySegmentTree<size_t> tree(arr);

	cout << tree.query(1, 5);
}

void extended_euclidean_test() {
	using namespace ExtendedEuclid;

	int a, b;
	scanf("%d %d", &a, &b);

	int re = extended_euclid(a, b);
	printf("%d %d %d\n", m, n, re);
}

void online_palindrome_check() {
	string s;
	cin >> s;
	OnlinePalindromeChecker checker;
	for (char c : s) {
		printf("%c : %d\n", c, checker.insertChar(c - 'a'));
	}
}

int main() {
	online_palindrome_check();
}