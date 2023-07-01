#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> dfs(int node, int colour, vector<int>& colours, vector<vector<int> >& edges, int vertex_count, int edges_count){
	pair<int, int> data;
	
	vertex_count++;
	colours[node] = colour;
	
	for (int x: edges[node]){
		if (colours[x] == -1){
			edges_count++;
		}
	}
	for (int x: edges[node]){
		if (colours[x] == -1){
			data = dfs(x, colour, colours, edges, vertex_count, edges_count);
			vertex_count = data.first;
			edges_count = data.second;
		}
	}
	
	return make_pair(vertex_count, edges_count);
}

int main(){
	int n, m;
	vector<int> colours;
	vector<vector<int> > edges;
	vector<pair<int, int> > input_edges;
	
	cin >> n >> m;
	
	for (int i = 0; i < n; i++){
		colours.push_back(-1);
		edges.push_back(vector<int>());
	}
	
	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		input_edges.push_back(make_pair(a, b));
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	
	int colour = -1;
	int current_colour = 0;
	int max_edges = 0;
	int max_vertex = 0;
	pair<int, int> current_data;
	for (int i = 0; i < n; i++){
		if (colours[i] == -1){
			current_data = dfs(i, current_colour, colours, edges, 0, 0);
			if (current_data.first > max_vertex){
				max_vertex = current_data.first;
				max_edges = current_data.second;
				colour = current_colour;
			}
			else if (current_data.first == max_vertex && current_data.second > max_edges){
				max_edges = current_data.second;
				colour = current_colour;
			}
			current_colour++;
		}
	}
	
	cout << "graph {" << endl;
	for (int i = 0; i < n; i++){
		cout << "    " << i;
		if (colours[i] == colour){
			cout << " [color = red]";
		}
		cout << endl;
	}
	for (int i = 0; i < m; i++){
		cout << "    " << input_edges[i].first << " -- " << input_edges[i].second;
		if (colours[input_edges[i].first] == colour){
			cout << " [color = red]";
		}
		cout << endl;
	}
	cout << "}" << endl;
}