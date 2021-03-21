// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int count(string line) {
	int counter = 0;

	for (char l = 'a'; l<='z'; ++l) {
		size_t found = line.find(l);
		if (found != string::npos) {
			counter++;
		}
	} 

	return counter;
}

int main() {

	string s, line;
	int total = 0;
	while (getline (cin, s)) {
		if (s.length() > 0) {
			line = line + s;
		} else {
			//cout << line << endl;
			total += count(line);
			line = "";
		}
	}

	cout << total << endl;
	
	return 0;
}