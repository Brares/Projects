// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

bool isValid(string line) {
	for (unsigned int i = 0; i < line.length(); i++) {
			if (line[i] == '-')
				line[i] = ' ';

			if (line[i] == ':')
				line[i] = ' ';
		}

	istringstream iss(line);
	
	int min = 0, max = 0;
	iss >> min >> max;

	char value;
	iss >> value;

	string passw;
	iss >> passw;

	int counter = 0;
	for (unsigned int i = 0; i < passw.length(); i++) {
		if (value == passw[i])
			counter++;
	}
	if (counter >= min && counter <= max)
		return true;
	return false;
}

int main() {
	string s;
	int counter = 0;
	//getline(cin, s);
	while (getline(cin, s)) {
		if (isValid(s))
			counter++;
	}

	cout << counter << endl;
	return 0;
}