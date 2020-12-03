//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

#define EVEN 1
#define HEAVY 50
#define LIGHT -50

bool checkHeavy(char c, string left[], string right[], string label[]) {
	for (int i = 0; i < 3; i++) {
		int Left = 0, Right = 0;
		for (unsigned int j = 0; j < left[i].length(); j++) {
			if (left[i][j] == c) 
				Left += HEAVY;
			else 
				Left += EVEN;
			if (right[i][j] == c) 
				Right += HEAVY;
			else 
				Right += EVEN;
		}
		if (label[i] == "even") {
			if(Left != Right) 
				return false;
		} else if (label[i] == "up") {
			if(Left <= Right) 
				return false;
		} else {
			if(Left >= Right) 
				return false;
		}
	}
	return true;
}

bool checkLight(char c, string left[], string right[], string label[]) {
	for (int i = 0; i < 3; i++) {
		int Left = 0, Right = 0;
		for (unsigned int j = 0; j < left[i].length(); j++) {
			if (left[i][j] == c) 
				Left += LIGHT;
			else 
				Left += EVEN;
			if (right[i][j] == c) 
				Right += LIGHT;
			else 
				Right += EVEN;
		}
		if (label[i] == "even") {
			if(Left != Right) 
				return false;
		} else if (label[i] == "up") {
			if(Left <= Right) 
				return false;
		} else {
			if(Left >= Right) 
				return false;
		}
	}
	return true;
}

int main() {
	int cases = 0;
	cin >> cases;
	while(cases--) {
		string left[3], right[3], label[3];
		for (int i = 0; i < 3; i++){
			cin >> left[i] >> right[i] >> label[i];
		}
		for (char c = 'A'; c != 'M'; c++) {
			if(checkHeavy(c, left, right, label)) {
				cout << c << " is the counterfeit coin and it is heavy." << endl;
				break;
			}
			else if (checkLight(c, left, right, label)) {
				cout << c << " is the counterfeit coin and it is light." << endl;
				break;
			}
		} 
	}
}