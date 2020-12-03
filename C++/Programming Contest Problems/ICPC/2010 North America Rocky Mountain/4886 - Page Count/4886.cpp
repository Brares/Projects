//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int pages = 0;
	while (cin >> pages && pages) {
		int counter = 0;
		int* index = new int[pages+2];
		string line;
		cin >> line;
		for (unsigned int i = 0; i < line.length(); i++) {
			if (line[i] == ',') {
				line[i] = ' ';
			}
		}
		istringstream iss(line);
		string word;
		while (iss >> word) {
			size_t found = word.find('-');
			if (found != string::npos) {
				word[found] = ' ';
				istringstream iss(word);
				int low, high;
				iss >> low >> high;
				if (low <= high) {
					for (int i = low; i <= high; i++) {
						if( i <= pages)
							index[i]++;
					}
				}
			} else {
				index[stoi(word)]++;
			}
		}
		for (int i = 1; i <= pages; i++) {
			if (index[i] != 0)
				counter++;
		}
		cout << counter << endl;
	}
}
