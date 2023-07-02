#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m, q, res_n;
vector<vector<int> > transitions, min_trans, can_trans;
vector<vector<string> > outputs, min_out, can_out;
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
			min_trans[i][j] = b[classes[transitions[a[i]][j]]];
			min_out[i][j] = outputs[a[i]][j];
		}
	}
}

void dfs(int state){
	visited[state] = true;
	transposition.push_back(state);
	for (int x: min_trans[state]){
		if (!visited[x]){
			dfs(x);
		}
	}
}

void canonize(vector<vector<int> >& canon_trans, vector<vector<string> >& canon_out){
	dfs(b[classes[q]]);
	for (int i = 0; i < transposition.size(); i++){
		rever[transposition[i]] = i;
	}
	for (int i = 0; i < res_n; i++){
		for (int j = 0; j < m; j++){
			canon_trans[i][j] = rever[min_trans[transposition[i]][j]];
			canon_out[i][j] = min_out[transposition[i]][j];
		}
	}
}

int main() {
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		transitions.push_back(vector<int>());
		outputs.push_back(vector<string>());
		min_trans.push_back(vector<int>());
		min_out.push_back(vector<string>());
		can_trans.push_back(vector<int>());
		can_out.push_back(vector<string>());
		visited.push_back(false);
		parent.push_back(0);
		depth.push_back(0);
		classes.push_back(0);
		a.push_back(0);
		b.push_back(0);
		for (int j = 0; j < m; j++) {
			transitions[i].push_back(0);
			outputs[i].push_back("");
			min_trans[i].push_back(-1);
			min_out[i].push_back("");
			can_trans[i].push_back(0);
			can_out[i].push_back("");
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
	canonize(can_trans, can_out);
	
	
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		visited[i] = false;
		parent[i] = 0;
		depth[i] = 0;
		classes[i] = 0;
		rever[i] = i;
		a[i] = 0;
		b[i] = 0;
		for (int j = 0; j < m; j++) {
			min_trans[i][j] = -1;
			min_out[i][j] = "";
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
		rever[i] = i;
	}
	transposition.clear();
	canonize(transitions, outputs);
	
	bool flag = true;
	for (int i = 0; i < res_n && flag; i++){
		for (int j = 0; j < m && flag; j++){
			flag = transitions[i][j] == can_trans[i][j] && outputs[i][j] == can_out[i][j];
		}
	}
	
	if (flag){
		cout << "EQUAL" << endl;
	}
	else{
		cout << "NOT EQUAL" << endl;
	}
}