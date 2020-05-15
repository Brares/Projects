// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int counter; // make this one global to know the number of correct answers

string calculation(string clueCode[10], int inPlace[10], int misplace[10], int g) {
	string result = "0000", guess;
	int j = 0;
	for (int i = 0; i < 10000; i++) {
		stringstream ss;
		ss << setw(4) << setfill('0') << i; // Found this way to add zeros at the beginning
		guess = ss.str();
		for (j = 0; j < g; j++) {
			int good = 0, bad = 0;
			map<char,int> check;
			for (int k = 0; k < 4; k++) {
				if (guess[k] == clueCode[j][k]) {
					good++, bad--;
					check[clueCode[j][k]]++;
				} else
					check[clueCode[j][k]]++;
			}
			for (int k = 0; k < 4; k++) {
				if (check[guess[k]] > 0 ) {
					bad++;
					check[guess[k]]-- ;
				}
			}
			if (inPlace[j] == good && misplace[j] == bad) {
				continue;
			} else
				break;
		}
		if (j == g) {
			counter++;
			result = guess;
			if (counter == 2)
				break;
		}
	}
	return result;
}
int main() {
	int n = 0;
	cin >> n;
	while (n--) {
		int g = 0;
		cin >> g;
		string clueCode[10];
		int inPlace[10], misplace[10];
		for (int i = 0; i < g; i++) {
			string clue;
			cin >> clueCode[i];
			cin >> clue;
			inPlace[i] = (int)clue[0] - 48;
			misplace[i] = (int)clue[2] - 48;
		}
		counter = 0;
		string answer = calculation(clueCode, inPlace, misplace, g);
		if (counter == 1)
			cout << answer << endl;
		else if (counter == 0)
			cout << "impossible" << endl;
		else
			cout << "indeterminate" << endl;
	}
	return 0;
}
