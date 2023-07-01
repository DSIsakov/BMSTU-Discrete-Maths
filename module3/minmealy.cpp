#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m, q, res_n;
vector<vector<int> > transitions, res_trans;
vector<vector<string> > outputs, res_out;
vector<int> parent, depth, classes, transposition, rever, a, b;
vector<bool> visited;

int Find(int x){
	if (x == parent[x]){
		return x;
	}
	parent[x] = Find(parent[x]);
	return parent[x];
}

void Union(int x, int y){
	x = Find(x), y = Find(y);
	if (x != y){
		if (depth[x] < depth[y]) {
			int temp = x;
			x = y;
			y = temp;
		}
		parent[y] = x;
		if (depth[x] == depth[y]) {
			depth[x]++;
		}
	}
}

int split1(){
	int m0 = n;
	for (int state = 0; state < n; state++){
		parent[state] = state;
		depth[state] = 0;
	}
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (Find(i) != Find(j)){
				bool eq = true;
				for (int k = 0; k < m; k++){
					if (outputs[i][k] != outputs[j][k]){
						eq = false;
						break;
					}
				}
				if (eq){
					Union(i, j);
					m0--;
				}
			}
		}
	}
	for (int i = 0; i < n; i++){
		classes[i] = Find(i);
	}

	return m0;
}

int split(){
	int m0 = n;
	for (int i = 0; i < n; i++){
		parent[i] = i;
		depth[i] = 0;
	}
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (classes[i] == classes[j] && Find(i) != Find(j)){
				bool eq = true;
				for (int k = 0; k < m; k++){
					if (classes[transitions[i][k]] != classes[transitions[j][k]]){
						eq = false;
						break;
					}
				}
				if (eq){
					Union(i, j);
					m0--;
				}
			}
		}
	}
	for (int i = 0; i < n; i++){
		classes[i] = Find(i);
	}
	
	return m0;
}

void minimize(){
	int m1 = split1(), m2;
	while (1){
		m2 = split();
		if (m1 == m2){
			break;
		}
		m1 = m2;
	}
	res_n = m1;
	// int max_class = 0;
	// for (int i = 0; i < n; i++){
	// 	while (classes[i] > max_class + 1){
	// 		for (int j = i; j < n; j++){
	// 			classes[j]--;
	// 		}
	// 	}
	// 	if (max_class < classes[i]) max_class++;
	// }
	int counter = 0;
	for (int i = 0; i < n; i++) {
		if (classes[i] == i) {
			a[counter] = i;
			b[i] = counter;
			counter++;
		}
	}
	for (int i = 0; i < res_n; i++) {
		for (int j = 0; j < m; j++) {
			res_trans[i][j] = b[classes[transitions[a[i]][j]]];
			res_out[i][j] = outputs[a[i]][j];
		}
	}
}

void dfs(int state){
	visited[state] = true;
	transposition.push_back(state);
	for (int x: res_trans[state]){
		if (!visited[x]){
			dfs(x);
		}
	}
}

void canonize(){
	dfs(b[classes[q]]);
	for (int i = 0; i < transposition.size(); i++){
		rever[transposition[i]] = i;
	}
	for (int i = 0; i < res_n; i++){
		for (int j = 0; j < m; j++){
			transitions[i][j] = rever[res_trans[transposition[i]][j]];
			outputs[i][j] = res_out[transposition[i]][j];
		}
	}
}

int main() {
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		transitions.push_back(vector<int>());
		outputs.push_back(vector<string>());
		res_trans.push_back(vector<int>());
		res_out.push_back(vector<string>());
		visited.push_back(false);
		parent.push_back(0);
		depth.push_back(0);
		classes.push_back(0);
		a.push_back(0);
		b.push_back(0);
		for (int j = 0; j < m; j++) {
			transitions[i].push_back(0);
			outputs[i].push_back("");
			res_trans[i].push_back(-1);
			res_out[i].push_back("");
			cin >> transitions[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> outputs[i][j];
		}
	}
	
	minimize();
	for (int i = 0; i < n; i++){
		visited[i] = false;
		rever.push_back(i);
	}
	canonize();
	
	cout << "digraph {" << endl << "	rankdir = LR" << endl;
	for (int i = 0; i < res_n; i++){
		for (int j = 0; j < m; j++) {
			cout << "	" << i << " -> " << transitions[i][j] << " [label = \"" << (char)('a'+j) << "(" << outputs[i][j] << ")\"]" << endl;
		}
	}
	cout << "}" << endl;
}