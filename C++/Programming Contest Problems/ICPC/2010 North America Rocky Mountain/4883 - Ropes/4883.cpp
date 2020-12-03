//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int values[3] = {50,60,70};

int main() {
	int n = 0;
	while ( cin >> n && n) {
		int* pitch = new int[n];
		int sum = 0;
		for (int i = 0; i < n; i++) {
			cin >> pitch[i];
			sum += pitch[i];
		}
		
		int* answer = new int[3];
		for (int i = 0; i < 3; i++) {
			if (values[i] >= sum*2) {
				int minimalValue = INT_MAX;
				for (int j = 0; j < n; j++) {
					int tmp = values[i] / pitch[j];
					if(tmp < minimalValue) {
						minimalValue = tmp;
					}
				}
				answer[i] = minimalValue;
			} else {
				answer[i] = -1;
			}
			if (i != 0) {
				cout << " " << answer[i] + 1 ;
			} else {
				cout << answer[i]+1;
			}
		}
		cout << endl;
	}
}
