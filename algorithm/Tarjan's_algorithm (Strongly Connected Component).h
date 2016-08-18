/*
* original : http://book.algospot.com/tarjan.html
*/
#pragma once
#include <vector>
#include <stack>
#include <algorithm>

namespace SCC {
	using namespace std;

	// �׷����� ���� ����Ʈ ǥ��
	vector<vector<int> > adj;

	// �� ������ ������Ʈ ��ȣ. ������Ʈ ��ȣ�� 0 ���� �����ϸ�, 
	// ���� ������ ������Ʈ�� ���� �������� ������Ʈ ��ȣ�� ����.
	vector<int> sccId;

	// �� ������ �߰� ������ scc() ���� ����
	vector<int> discovered, finished;

	// ������ ��ȣ�� ��� ����
	stack<int> st;

	int sccCounter, vertexCounter;

	// here �� ��Ʈ�� �ϴ� ����Ʈ������ ������ �������� ���� �� �ִ� �ּ��� �߰� ������
	// ��ȯ�Ѵ�.
	int scc(int here) {
		int ret = discovered[here] = vertexCounter++;
		// ���ÿ� here �� �ִ´�. here �� �ļյ��� ��� ���ÿ��� here �Ŀ� ����.
		st.push(here);
		for (int there : adj[here]) {
			// (here,there) �� Ʈ�� ����
			if (discovered[there] == -1)
				ret = min(ret, scc(there));
			// (here,there) �� �������̳� ���� ����
			else if (discovered[there] < discovered[here] && sccId[there] == -1)
				ret = min(ret, discovered[there]);
		}
		// here �� ������ ������Ʈ�� ��Ʈ�ΰ� Ȯ���Ѵ�
		if (ret == discovered[here]) {
			// here �� ��Ʈ�� �ϴ� ����Ʈ���� ���� �ִ� �������� ���� �ϳ��� ������Ʈ�� ���´�
			while (true) {
				int t = st.top();
				st.pop();
				sccId[t] = sccCounter;
				if (t == here) break;
			}
			++sccCounter;
		}
		finished[here] = 1;
		return ret;
	}

	// tarjan �� SCC �˰���
	vector<int>& tarjanSCC() {
		// �迭���� ���� �ʱ�ȭ
		sccId.resize(adj.size());
		fill(sccId.begin(), sccId.end(), -1);
		discovered.resize(adj.size());
		fill(discovered.begin(), discovered.end(), -1);

		finished.resize(adj.size());
		fill(finished.begin(), finished.end(), 0);

		// ī���� �ʱ�ȭ
		sccCounter = vertexCounter = 0;
		// ��� ������ ���� scc() ȣ��
		for (int i = 0; i < adj.size(); i++) if (discovered[i] == -1) scc(i);
		return sccId;
	}
}