// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 0, m = 0, counter = 0;
	while (cin >> n >> m && n && m) {
		if (counter != 0)
			cout << endl;
		char table[150][150];
		int ans[150][150];
		counter++;
		for (int i = 0; i < n + 2; i++) {
			for (int j = 0; j < m+2; j++) {
				if (i > 0 && j > 0 && i < n+1 && j < m+1)
					cin >> table[i][j];
				else
					table[i][j] = '.';
				ans[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if ( table[i][j] == '*') {
					for (int y = -1; y < 2; y++) {
						for (int z = -1; z < 2; z++)
							ans[i+y][j+z]++;
					}
						
				}
			}
		}
		cout << "Field #" << counter << ":" << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if ( table[i][j] == '*') {
					cout << '*';
				} else {
					cout << ans[i][j];
				}
			}
			cout << endl;
		}	
	}
	return 0;
}
