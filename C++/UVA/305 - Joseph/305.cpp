//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int k = 1;
	int m = 0;
	int index = 0;
	int total  = 0;
	int answers[13];
	while (k != 14) {
		index = 0;
		total = 2 * k;
		m = k + 1;
		for (m; m < INT_MAX ; m++) { // I did not know the maximum number of m, so put the INT_MAX
			index = 0;			
			bool flag = true;			
			for (int j = 0; j < k; j++) {
				index = ((index + m - 1)%(total));				
				total--;
				if (index < k) {
					total = 2 * k;
					flag = false;
					break;
				}			
			}
			if (flag) {
				break;			
			}
		}
		answers[k - 1] = m; // Following advice. All the answers are stored in an array 
		k++;
	}
	while (cin >> k && k) { 
		cout << answers[k-1] << endl; //When reading k, takes the answer from the array.
	}
	return 0;
}
