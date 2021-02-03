// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 0, counter = 0;
	int number[200000];
	while( cin >> n && n) {
		number[counter++] = n;
	}
	for( int i = 0; i < counter; i++) {
		for( int j = 0; j < counter; j++) {
			for( int k = 0; k < counter; k++) {
				if( i != j && i != k && j != k) {
					if( number[i] + number[j] + number[k] == 2020) {
						cout << number[i] * number[j] * number[k] << endl;
						return 0;
				}
			}
			}
		}
	}

	return 0;
}