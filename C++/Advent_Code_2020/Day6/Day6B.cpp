// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int count(string line, int group) {
	int counter = 0;

	for (char l = 'a'; l<='z'; l++) {
		int tmpCounter = 0;
		for (unsigned int i = 0; i < line.length(); i++) {
			if (line[i] == l){
				tmpCounter++;

				if (tmpCounter == group) {
					//cout << "counter: " << counter << " " << l << endl ;
					counter++;
				}
			}
			
		}
	} 

	return counter;
}

int main() {

	string s, line;
	int total = 0, group = 0;
	while (getline (cin, s)) {
		if (s.length() > 0) {
			line = line + s;
			group++;
		} else {
			//cout << group << line << endl;

			total += count(line, group);
			line = "";
			group = 0;
		}
	}

	cout << total << endl;
	
	return 0;
}