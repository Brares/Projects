// Jonathan Flores

#include <bits/stdc++.h> 

using namespace std;

int main() {
	long int n = 0;
	long int m = 0;
	long int total = 0;
	while (cin >> n >> m) {
		if (n >= m)	
			total = n - m;
		else
			total = m - n;
		cout << total << endl;
	}
	return 0;
}
