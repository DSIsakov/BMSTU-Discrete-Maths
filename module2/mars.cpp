#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

bool check(int node, vector<int> colours, vector<vector<int> >& edges){
	for (int x: edges[node]){
		if (colours[x] == colours[node]){
			return false;
		}
	}
	
	return true;
}

vector<int> dfs(int node, vector<int> colours, vector<vector<int> >& edges){
	if (node == colours.size()){
		colours.push_back(2);
		return colours;
	}
	if (colours[node] == -1){
		vector<int> colours1 = colours;
		
		colours[node] = 0;
		if (check(node, colours, edges)){
			for (int x: edges[node]){
				colours[x] = 1;
			}
			colours = dfs(node + 1, colours, edges);
		}
		else {
			colours.push_back(-2);
		}
		
		colours1[node] = 1;
		if (check(node, colours1, edges)){
			for (int x: edges[node]){
				colours1[x] = 0;
			}
			colours1 = dfs(node + 1, colours1, edges);
		}
		else {
			colours1.push_back(-2);
		}
		
		if (colours.back() == 2 && colours1.back() == 2){
			int first = 0;
			int second = 0;
			int first1 = 0;
			int second1 = 0;
			
			for (int i = 0; i < colours.size() - 1; i++){
				if (colours[i] == 0){
					first++;
				}
				else{
					second++;
				}
				
				if (colours1[i] == 0){
					first1++;
				}
				else{
					second1++;
				}
			}
			
			if (abs(first - second) < abs(first1 - second1)){
				return colours;
			}
			else if (abs(first - second) == abs(first1 - second1)){
				if (first <= second){
					return colours;
				}
				else {
					return colours1;
				}
			}
			else {
				return colours1;
			}
		}
		else if (colours1.back() == 2) {
			return colours1;
		}
		else {
			return colours;
		}
	}
	else {
		if (check(node, colours, edges)){
			for (int x: edges[node]){
				colours[x] = 1 - colours[node];
			}
			colours = dfs(node + 1, colours, edges);
		}
		else{
			colours.push_back(-2);
		}
		
		return colours;
	}
}

int main(){
	int n;
	vector<int> colours;
	vector<vector<int> > edges;
	cin >> n;
	
	for (int i = 0; i < n; i++){
		colours.push_back(-1);
		vector<int> v;
		for (int j = 0; j < n; j++){
			char c;
			cin >> c;
			if (c == '+'){
				v.push_back(j);
			}
		}
		edges.push_back(v);
	}
	
	colours[0] = 0;
	colours = dfs(0, colours, edges);
	
	if (colours.back() == 2){
		int first = 0;
		int second = 0;
		for (int i = 0; i < n; i++){
			if (colours[i] == 0){
				first++;
			}
			else{
				second++;
			}
		}
		
		if (first <= second){
			for (int i = 0; i < n; i++){
				if (colours[i] == 0){
					cout << i + 1 << " ";
				}
			}
		}
		else{
			for (int i = 0; i < n; i++){
				if (colours[i] == 1){
					cout << i + 1 << " ";
				}
			}
		}
	}
	else {
		cout << "No solution";
	}
	cout << endl;
}