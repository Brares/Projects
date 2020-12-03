// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	map<char,string> table;
	table['a'] = "0110000000";
	table['b'] = "0100000000";
	table['c'] = "0111001111";
	table['d'] = "0111001110";
	table['e'] = "0111001100";
	table['f'] = "0111001000";
	table['g'] = "0111000000";
	table['A'] = "1110000000";
	table['B'] = "1100000000";
	table['C'] = "0010000000";
	table['D'] = "1111001110";
	table['E'] = "1111001100";
	table['F'] = "1111001000";
	table['G'] = "1111000000";
	int t = 0;
	cin >> t;
	cin.clear();
	cin.ignore();
	while(t--) {
		int fingers[10];
		for (int i = 0; i < 10; i++)
			fingers[i] = 0;
		string line;
		getline(cin,line);
		string old = "";
		for (unsigned int i = 0; i < line.length(); i++) {
			string actual = table[line[i]];
			for(unsigned int j = 0; j < actual.length(); j++) {				
				if (actual[j] == '1' && i == 0) {
					fingers[j]++;				
				}
			 	else if (old[j] == '0' && actual[j] == '1') {
					fingers[j]++;
				}
			}
			old = actual;
		}
		for (int i = 0; i < 9; i++)
			cout << fingers[i] << " ";
		cout << fingers[9]; // I was getting presentation error before doing this
		cout << endl;
	}
	return 0;
}
