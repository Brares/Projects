// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int answer, n;
bool ld[30]; // Double the size of the original limit
bool rd[30]; // Double the size of the original limit
bool cl[15]; // Size of the limit

void solution(bool board[15][15], int col) { //Starts Recursion at Colum = 0
	if(col == n) {
		answer++;
	}
	for (int i = 0 ; i < n; i++) { //Check every Row
		if ((ld[i - col + n] != 1 && rd[i + col] != 1) && cl[i] != 1 && board[i][col] != 1) {
			ld[i - col + n] = 1;
			rd[i + col] = 1;
			cl[i] = 1;

			solution(board, col + 1);
			ld[i - col + n] = 0;
			rd[i + col] = 0;
			cl[i] = 0;
		}
	}
}

int main() {
	n = 0;
	int counter = 0;
	while (cin >> n && n) {
		counter++;
		cin.clear();
		cin.ignore();
		bool board[15][15];
		for (int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if (c == '.')
					board[i][j] = 0;
				else
					board[i][j] = 1;;
			}
		}
		answer = 0;
		solution(board, 0);
		cout << "Case " << counter << ": " << answer<< endl;
	}
	return 0;
}
