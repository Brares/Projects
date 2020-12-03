// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int k = 0, copy = 0;
	cin >> k;
	copy = k;
	string s;
	while (k--) {
		if (copy != k+1)
			cout << endl;
		getline(cin,s);
		int m = 0, n = 0, index = 0;
		priority_queue <int> max;
		priority_queue <int, vector<int>, greater<int>> min;
		vector<int> a;
		vector<int> u;
		cin >> m >> n;
		for (int i = 0; i < m ; i++) {
			int tmp = 0;
			cin >> tmp;
			a.push_back(tmp);
		}
		for (int i = 0; i < n; i++) {
			int tmp = 0;
			cin >> tmp;
			u.push_back(tmp);
		}
		for (int i = 0; i < n; i ++) {
			for (int j = index; j < u[i]; j++) {
				if (i == 0 || a[j] <= max.top())
					max.push(a[j]);
				else
					min.push(a[j]);
				if (max.size() > i+1) {
					min.push(max.top());
					max.pop();
				}
				index++;
			}
			if (max.size() < i+1) {
					max.push(min.top());
					min.pop();
			}
			cout << max.top() << endl;
		}
	}
}
