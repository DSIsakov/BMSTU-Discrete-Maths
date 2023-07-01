#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	int n, m, q;
	vector<vector<int> > d;
	vector<vector<string> > f;
	cin >> n >> m >> q;
	
	for (int i = 0; i < n; i++){
		vector<int> vd;
		for (int j = 0; j < m; j++){
			int x;
			cin >> x;
			vd.push_back(x);
		}
		d.push_back(vd);
	}
	for (int i = 0; i < n; i++){
		vector<string> vf;
		for (int j = 0; j < m; j++){
			string x;
			cin >> x;
			vf.push_back(x);
		}
		f.push_back(vf);
	}
	
	cout << "digraph {" << endl;
	cout << "    rankdir = LR" << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << "    " << i << " -> " << d[i][j] << " [label = \"" << (char)('a' + j) << "(" << f[i][j] << ")\"]" << endl;
		}
	}
	cout << "}" << endl;
}