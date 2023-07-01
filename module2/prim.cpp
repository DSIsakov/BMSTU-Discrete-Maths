#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int n, m;
	vector<vector<pair<int, int> > > g;
	vector<bool> visited;
	vector<int> min_edge;
	vector<int> sel_edge;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	
	cin >> n >> m;
	for (int i = 0; i < n; i++){
		g.push_back(vector<pair<int, int> >());
		visited.push_back(false);
		min_edge.push_back(2000000000);
		sel_edge.push_back(-1);
	}
	
	for (int i = 0; i < m; i++) {
		int u, v, len;
		cin >> u >> v >> len;
		g[u].push_back(make_pair(v, len));
		g[v].push_back(make_pair(u, len));
	}

	int result = 0;
	min_edge[0] = 0;
	q.push(make_pair(0, 0));
	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		if (visited[v]) continue;
		visited[v] = true;
		result += min_edge[v];
		for (auto edge : g[v]) {
			int to = edge.first, len = edge.second;
			if (len < min_edge[to] && !visited[to]) {
				sel_edge[to] = v;
				min_edge[to] = len;
				q.push(make_pair(min_edge[to], to));
			}
		}
	}

	cout << result << endl;
}