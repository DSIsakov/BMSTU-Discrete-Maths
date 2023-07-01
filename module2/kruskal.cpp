#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Vertex {
	int x, y;
};

struct Edge {
	int u, v;
	double w;
};

bool compare(const Edge& a, const Edge& b) {
	return a.w < b.w;
}

int find(int x, vector<int>& parent) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = find(parent[x], parent);
}

void unite(int x, int y, vector<int>& parent) {
	int px = find(x, parent), py = find(y, parent);
	parent[px] = py;
}

int main() {
	int n;
	vector<int> parent;
	vector<Vertex> vertex;
	vector<Edge> edges;
	double result = 0;
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		Vertex v = {x, y};
		vertex.push_back(v);
		parent.push_back(i);
		for (int j = 0; j < i; j++) {
			Edge e = {i, j, sqrt((vertex[i].x - vertex[j].x) * (vertex[i].x - vertex[j].x) + (vertex[i].y - vertex[j].y) * (vertex[i].y - vertex[j].y))};
			edges.push_back(e);
		}
	}
	
	sort(edges.begin(), edges.end(), compare);
	for (int i = 0; i < edges.size(); i++) {
		int u = edges[i].u, v = edges[i].v;
		double w = edges[i].w;
		if (find(u, parent) != find(v, parent)){
			unite(u, v, parent);
			result += w;
		}
	}
	
	cout.precision(2);
	cout << fixed << result << endl;
}