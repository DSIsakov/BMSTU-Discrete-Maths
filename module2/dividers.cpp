#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
bool compare(T a, T b){
	return a > b;
}

bool isPrime(long long x){
	if ((x % 2 == 0 && x > 2) || (x % 3 == 0 && x > 3)){
		return false;
	}
	for (long long i = 6; i * i <= x + 2 * i; i += 6){
		if (x % (i-1) == 0 || x % (i+1) == 0){
			return false;
		}
	}
	
	return true;
}

int main(){
	long long n;
	vector<long long> dividers;
	
	cin >> n;
	
	long long i;
	for (i = 1; i * i < n; i++){
		if (n % i == 0){
			dividers.push_back(i);
			dividers.push_back(n / i);
		}
	}
	if (i * i == n){
		dividers.push_back(i);
	}
	
	sort(dividers.begin(), dividers.end(), compare<long long>);
	cout << "graph {" << endl;
	for (auto divider: dividers){
		cout << "    " << divider << endl;
	}
	for (int first = 0; first < dividers.size(); first++){
		for (int second = first + 1; second < dividers.size(); second++){
			if (dividers[first] % dividers[second] == 0 && isPrime(dividers[first] / dividers[second])){
				cout << "    " << dividers[first] << "--" << dividers[second] << endl;
			}
		}
	}
	cout << "}" << endl;
}