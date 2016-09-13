/*
 * JUST FOR TEST!
 */
#include "algorithm/data structure/lazy_propagation_segment_tree.h"
#include "algorithm/data structure/segment_tree.h"
#include "algorithm/data structure/union-find.h"
#include "algorithm/etc/fast_specific_digit_count_in_integer(0_to_N).h"
#include "algorithm/geometry/convex_hull.h"
#include "algorithm/graph/bellman-ford.h"
#include "algorithm/graph/Bipartite graph matching (using Ford-Fulkerson's algorithm).h"
#include "algorithm/graph/bipartite_graph_tester.h"
#include "algorithm/graph/dijkstra.h"
#include "algorithm/graph/Edmonds-Karp algorithm (maximum flow).h"
#include "algorithm/graph/floyd-warshall.h"
#include "algorithm/graph/Hopcroft-Karp algorithm (bipartite graph maximum matching).h"
#include "algorithm/graph/Kosaraju's_algorithm (Strongly Connected Component).h"
#include "algorithm/graph/prim.h"
#include "algorithm/graph/SPFA (Shortest Path Faster Algorithm).h"
#include "algorithm/graph/Tarjan's_algorithm (Strongly Connected Component).h"
#include "algorithm/math/extended_euclidean.h"
#include "algorithm/math/fast_binomial_coefficient.h"
#include "algorithm/math/maximum_subarray_sum.h"
#include "algorithm/string/aho-corasick.h"
#include "algorithm/string/boyer-moore.h"
#include "algorithm/string/KMP.h"
#include "algorithm/string/Manacher's_algorith (all palindrome).h"
#include "algorithm/string/online_palindrome_check.h"
#include "algorithm/string/suffix_array_lcp.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;


void primTest() {
	size_t n, t;
	cin >> n >> t;

	prim::G.resize(n);
	for (size_t i = 0; i < t; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		prim::G[a].emplace_back(c, b);
	}

	auto re = prim::prim();

	for (auto i = 0; i < re.size(); i++) {
		for (auto &p : re[i]) {
			printf("(%d -> %d) ", i, p.second);
		}
	}
}

void bellmanTest() {
	size_t n, t;
	cin >> n >> t;

	BellmanFord::G.resize(n);
	for (size_t i = 0; i < t; i++) {
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

void extendedEuclideanTest() {
	using namespace ExtendedEuclid;

	int a, b;
	scanf("%d %d", &a, &b);

	int re = extended_euclid(a, b);
	printf("%d %d %d\n", m, n, re);
}

void onlinePalindromeCheck() {
	string s;
	cin >> s;
	OnlinePalindromeChecker checker;
	for (char c : s) {
		printf("%c : %d\n", c, checker.insertChar(c - 'a'));
	}
}

void fordFulkersonTest() {
	size_t n, k, a, b;
	cin >> n >> k;

	vector<vector<size_t>> flow(n, vector<size_t>(n, 0)), map(n);
	for (size_t i = 0; i < k; i++) {
		cin >> a >> b;
		map[a].emplace_back(b);
		cin >> flow[a][b];
	}

	using namespace EdmondsKarp;

	cout << edmondsKarp(map, flow, 0, n - 1) << endl;
}

void SPFATest() {
	size_t start, n, e, a, b;
	int w;

	cin >> n >> e >> start;
	start--;
	vector<vector<pair<int, size_t>>> graph(n);
	while (e--) {
		cin >> a >> b >> w;
		a--, b--;
		graph[a].emplace_back(w, b);
	}

	auto &s = SPFA::spfa(graph, start);
	for (auto v : s) cout << v << endl;
}

void kosarajuTest() {
	size_t n, m, a, b;
	cin >> n >> m;

	vector<vector<size_t>> map(n), revMap(n);

	while (m--) {
		cin >> a >> b;
		a--, b--;
		map[a].emplace_back(b);
		revMap[b].emplace_back(a);
	}

	const auto &arr = SCC::SCC(map, revMap);
	for (auto v : arr) printf("%zu ", v);
	puts("");
}

void targanTest() {
	int n, m, a, b;

	auto &arr = SCC::adj;
	cin >> n >> m;
	arr.resize(n);

	while (m--) {
		cin >> a >> b;
		a--, b--;
		arr[a].emplace_back(b);
	}

	const auto &ret = SCC::tarjanSCC();
	for (auto v : ret) printf("%d ", v);
}

void hopcroftKarpTest() {
	size_t n, t, a;
	cin >> n;

	vector<vector<size_t>> graph(n);
	for (size_t i = 1; i <= n; i++) {
		cin >> t;
		while (t--) {
			cin >> a;
			graph[i].emplace_back(a);
		}
	}

	cout << HopcroftKarp::maximumMatching(graph, n, n);
}

int main() {
	hopcroftKarpTest();
}