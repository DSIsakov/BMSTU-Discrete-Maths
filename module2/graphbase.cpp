#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void tarjan(int node, int& timer, vector<vector<int> >& edges, vector<int>& tin, vector<int>& low, stack<int>& s, vector<int>& comp, int& count){
	tin[node] = low[node] = timer++;
	s.push(node);
	for (int x : edges[node]) {
		if (tin[x] == 0) {
			tarjan(x, timer, edges, tin, low, s, comp, count);
		}
		if (comp[x] == 0 && low[node] > low[x]) low[node] = low[x];
	}
	
	if (tin[node] == low[node]) {
		int x;
		do {
			x = s.top();
			s.pop();
			comp[x] = count;
		} while (node != x);
		count++;
	}
}

int main(){
	int n, m, timer = 1, count = 1;
	vector<vector<int> > edges;
	vector<int> tin, low, comp;
	stack<int> s;
	
	cin >> n >> m;
	for (int i = 0; i < n; i++){
		edges.push_back(vector<int>());
		tin.push_back(0);
		low.push_back(0);
		comp.push_back(0);
	}
	for (int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
	}
	
	for (int i = 0; i < n; i++){
		if (tin[i] == 0) {
			tarjan(i, timer, edges, tin, low, s, comp, count);
		}
	}
	
	vector<bool> components(n, false);
	
	for (int i = 0; i < n; i++){
		components[comp[i]] = true;
	}
	
	for (int i = 0; i < n; i++){
		for (int x: edges[i]){
			if (comp[i] != comp[x]){
				components[comp[x]] = false;
			}
		}
	}
	
	for (int i = 0; i < n; i++){
		if (components[comp[i]]){
			cout << i << " ";
			components[comp[i]] = false;
		}
	}
	cout << endl;
}