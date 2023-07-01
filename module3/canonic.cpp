#include <iostream>
#include <utility>
#include <vector>
#include <string> 

using namespace std;

vector<vector<int> > transition;
vector<vector<string> > output;
vector<int> transposition, reverse;
vector<bool> visited;

void dfs(int state){
	visited[state] = true;
	transposition.push_back(state);
	for (int x: transition[state]){
		if (!visited[x]){
			dfs(x);
		}
	}
}

int main(){
	int n, m, q;
	cin >> n >> m >> q;
	
	for (int i = 0; i < n; i++){
		transition.push_back(vector<int>());
		visited.push_back(false);
		::reverse.push_back(i);
		for (int j = 0; j < m; j++){
			int x;
			cin >> x;
			transition[i].push_back(x);
		}
	}
	for (int i = 0; i < n; i++){
		output.push_back(vector<string>());
		for (int j = 0; j < m; j++){
			string x;
			cin >> x;
			output[i].push_back(x);
		}
	}
	
	dfs(q);
	
	for (int i = 0; i < n; i++){
		::reverse[transposition[i]] = i;
	}
	
	cout << n << endl << m << endl << 0 << endl;
	for (int state: transposition){
		for (int x: transition[state]){
			cout << ::reverse[x] << " ";
		}
		cout << endl;
	}
	
	for (int state: transposition){
		for (string x: output[state]){
			cout << x << " ";
		}
		cout << endl;
	}
}