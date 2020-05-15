// Jonathan Flores

#include <bits/stdc++.h> 

using namespace std;

int main() {
	int n = 0;
	cin >> n;
	map<string, unsigned> countries;
	for (int i = 0; i < n; i++) {
			char line[76];	
			cin >> line; // I wanted to use getline, but I did this way
			char* country = strtok(line, " ");
			cin.clear(); // Have problems with this part
			cin.ignore(76, '\n'); 						
			++countries[country]; 
	}
	for (auto const& pr : countries) { // Look on Internet how to read a map because I am not used using Maps
		cout << pr.first << " " << pr.second << endl;
	}
	return 0;
}
