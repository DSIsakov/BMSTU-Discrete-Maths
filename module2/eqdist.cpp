#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs(int start, int n, vector<vector<int> >& edges, vector<bool> visited){
	queue<int> queue;
	vector<int> dist (n, 0);
	queue.push(start);
	visited[start] = true;
	while (!queue.empty()){
		int node = queue.front();
		queue.pop();
		for (int x: edges[node]){
			if (!visited[x]){
				queue.push(x);
				dist[x] = dist[node] + 1;
				visited[x] = true;
			}
		}
	}
	
	return dist;
}

int main(){
	int n, m, k;
	cin >> n >> m;
	
	vector<vector<int> > edges;
	vector<vector<int> > dist;
	vector<bool> visited (n, false);
	
	for (int i = 0; i < n; i++){
		edges.push_back(vector<int>());
		visited[i] = false;
	}
	
	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	
	cin >> k;
	for (int i = 0; i < k; i++){
		int x;
		cin >> x;
		dist.push_back(bfs(x, n, edges, visited));
	}
	
	bool flag = false;
	for (int i = 0; i < n; i++){
		int j;
		for (j = 1; j < k; j++){
			if (dist[j][i] != dist[j-1][i]){
				break;
			}
		}
		if (j == k && dist[0][i] != 0) {
			cout << i << " ";
			flag = true;
		}
	}
	if (!flag) cout << "-";
	cout << endl;
	// for (int i = 0; i < k; i++){
	// 	for (int j = 0; j < n; j++){
	// 		cout << dist[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
}