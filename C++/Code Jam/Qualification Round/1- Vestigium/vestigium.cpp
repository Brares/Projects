//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

bool row[102];
bool col[102]; 

int main() {
	int cases = 0;
	cin >> cases;
	int counter = 1;
	while (cases--) {
		int n = 0;
		cin >> n;
		int board[102][102];
		int trace = 0, colN = 0, rowN = 0;
		vector<vector<int>> rows;
		for (int i = 0; i < n; i++) {
			col[i] = 0;
			row[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			int* rows = new int[n+2];
			for(int j = 0; j < n; j++) {
				int tmp = 0;
				cin >> tmp;
				board[i][j] = tmp;
				rows[tmp]++;
				if (rows[tmp] == 2 && row[i] == 0) {
					row[i] = 1;
					rowN++;
				}
				if (i == j)
					trace += tmp;
			}
		}

		for (int i = 0; i < n; i++) {
			int* rows = new int[n+2];
			for(int j = 0; j < n; j++) {
				int tmp = board[j][i];
				rows[tmp]++;
				if (rows[tmp] == 2 && col[i] == 0) {
					col[i] = 1;
					colN++;
				}
			}
		}

		cout << "Case #" << counter++ << ": " << trace << " " << rowN << " " << colN << endl;
	}
	return 0;
}