//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int rail1[1001], rail2[1001], finalRail[2002];
int n1, n2;
bool dp[1001][1001] = {false};

bool recursion(int i, int j, int k) {
	if (i >= n1 && j >= n2)
		return true;
	bool answer = false;
	if (dp[i][j] == true) {
		return false;
	}
	if(rail1[i] == finalRail[k] || rail2[j] == finalRail[k]) {
		if(rail1[i] == finalRail[k] && i < n1)
			answer = recursion(i+1, j, k+1);
		dp[i+1][j] = true;
		if (answer == true)
			return true;
		if (rail2[j] == finalRail[k] && j < n2)
			answer = recursion(i, j+1, k+1);
		dp[i][j+1] = true;
		if (answer == true)
			return true;
	} else {
		return false;
	}
	return false;
}

int main() {
	while (cin >> n1 >> n2 && n1 && n2) {
		for (int i = 0; i < n1; i++) {
			cin >> rail1[i];
		}

		for (int i = 0; i < n2; i++) {
			cin >> rail2[i];
		}

		for (int i = 0; i < n1+n2; i++) {
			cin >> finalRail[i];
		}
		for (int i = 0; i <= n1; i++) {
			for (int j = 0; j <= n2; j++) {
				dp[i][j] = false;
			}
		}
		bool answer = recursion(0,0,0);
		if (answer == true)
			cout << "possible" << endl;
		else
			cout << "not possible" << endl;
	}
}
