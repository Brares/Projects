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
			if( j != i) {
				if( number[i] + number[j] == 2020) {
					cout << number[i] * number[j] << endl;
					return 0;
				}
			}
		}
	}
	
	return 0;
}