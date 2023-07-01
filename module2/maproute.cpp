#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

struct Point{
	int w, min;
	pair<int, int> parent;
};

vector<pair<int, int> > getNeighbours(int x, int y, int n, vector<vector<Point> >& map){
	vector<pair<int, int> > neighbours;
	int px = map[x][y].parent.first;
	int py = map[x][y].parent.second;
	if (x > 0){
		neighbours.push_back(make_pair(x-1, y));
	}
	if (y > 0){
		neighbours.push_back(make_pair(x, y-1));
	}
	if (x < n - 1){
		neighbours.push_back(make_pair(x+1, y));
	}
	if (y < n-1){
		neighbours.push_back(make_pair(x, y+1));
	}
	return neighbours;
}

void dfs(vector<vector<Point> >& map, int n){
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > q;
	q.push(make_pair(map[0][0].min, make_pair(0, 0)));
	while (!q.empty()) {
		pair<int, pair<int, int> > v = q.top();
		int x = v.second.first, y = v.second.second;
		q.pop();
		vector<pair<int, int> > neighbours = getNeighbours(x, y, n, map);
		for (auto neighbour: neighbours){
			int i = neighbour.first, j = neighbour.second;
			if (v.first + map[i][j].w < map[i][j].min){
				map[i][j].min = v.first + map[i][j].w;
				map[i][j].parent = make_pair(x, y);
				q.push(make_pair(map[i][j].min, make_pair(i, j)));
			}
		}
	}
}

int main(){
	int n;
	vector<vector<Point> > map;
	
	cin >> n;
	for (int i = 0; i < n; i++){
		map.push_back(vector<Point>());
		for (int j = 0; j < n; j++){
			int x;
			cin >> x;
			map[i].push_back(Point());
			map[i][j].min = 2000000000;
			map[i][j].w = x;
			map[i][j].parent = make_pair(-1, -1);
		}
	}
	
	map[0][0].min = map[0][0].w;
	dfs(map, n);
	
	cout << map[n-1][n-1].min << endl;
}