// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;


int main() {

	string s, line;
	while (getline (cin, s)) {
		if (s.length() > 0) {

			line = line + s;

		} else {
			cout << line << endl;
			line = "";
		}
	}
	
	return 0;
}