#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void dfs(int node, int prev, pair<int, int>& data, vector<vector<int> >& edges, vector<int>& tin, vector<int>& low){
	tin[node] = low[node] = ++data.first;
	for (int x : edges[node]) {
		if (x == prev) continue;
		if (tin[x] == 0) {
			dfs(x, node, data, edges, tin, low);
			if (low[node] > low[x]) low[node] = low[x];
			if (low[x] > tin[node]) {
				data.second++;
			}
		} else {
			low[node] = min(low[node], tin[x]);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<int> > edges;
	vector<int> tin, low;
	pair<int, int> data = make_pair(0, 0);
	
	for (int i = 0; i < n; i++){
		edges.push_back(vector<int>());
		tin.push_back(0);
		low.push_back(0);
	}
	
	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	for (int i = 0; i < n; i++){
		if (tin[i] == 0) {
			dfs(i, -1, data, edges, tin, low);
		}
	}
	
	cout << data.second << endl;

	return 0;
}