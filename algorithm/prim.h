#pragma once
#include <queue>
#include <vector>
#include <limits>
#include <functional>

namespace prim {
	typedef std::pair<int, int> PAIR;

	const int &INF = std::numeric_limits<int>::max();

	/*
	Graph
	pair.first : weight
	pair.second : destination node
	*/
	std::vector<std::vector<PAIR> > G, MST;

	std::vector<bool> selected;
	std::vector<PAIR> dist;


	std::vector<std::vector<PAIR> >& prim() {
		const size_t &n = G.size();
		size_t cnt = n - 1;

		MST.resize(n, std::vector<PAIR>(0));

		selected.resize(n, false);
		dist.resize(n, std::make_pair(INF, 0));

		std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR> > que;

		dist[0] = std::make_pair(0, 0);
		selected[0] = true;
		que.push(std::make_pair(-1, 0));

		while (cnt != 0) {
			PAIR t = que.top();
			que.pop();

			int here = t.second;
			const int &prev = dist[here].second;

			if (here != 0) {
				if (selected[here]) continue;

				MST[prev].push_back(std::make_pair(dist[here].first, here));
				MST[here].push_back(std::make_pair(dist[here].first, prev));

				selected[here] = true;
				cnt--;
			}

			for (std::vector<PAIR>::iterator i = G[here].begin(); i != G[here].end(); i++) {
				const int &there = i->second;
				const int &weight = i->first;

				if (!selected[there] && dist[there].first > weight) {
					dist[there].first = weight;
					dist[there].second = here;

					que.push(std::make_pair(weight, there));
				}
			}
		}

		return MST;
	}
}

/*
7 9
0 1 8
0 6 10
1 5 9
1 2 11
2 5 13
2 3 8
3 4 7
4 5 12
5 6 5
*/