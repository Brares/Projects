//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int cases = 0;
	cin >> cases;
	int counter = 1;
	while (cases--) {
		string s, answer;
		cin >> s;
		int n = s.length();
		int leftSide = 0, rightSide = 0;
		for (int i = 0; i < n; i++) {
			int tmp = (int)s[i]-48;
			while(rightSide < leftSide && tmp < leftSide) {
				answer += ")";
				rightSide++;
				leftSide--;
			}
			while (leftSide < tmp) {
				answer += "(";
				leftSide++;
				rightSide--;
			}
			answer += to_string(tmp);
		}
		while(rightSide < leftSide) {
				answer += ")";
				rightSide++;
				leftSide--;
			}

		cout << "Case #" << counter++ << ": " << answer << endl;
	}
	return 0;
}