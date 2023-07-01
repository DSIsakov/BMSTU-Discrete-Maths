#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m, q, res_n;
vector<vector<int> > transitions, min_trans, can_trans;
vector<vector<string> > outputs, min_out, can_out;
vector<int> parent, depth, classes, transposition, rever, delta, a, b;
vector<bool> visited;
