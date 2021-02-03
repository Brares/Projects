// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

void clearMap(map<string, int> &table) {
	for (auto &pr : table) { 
		pr.second = 0;
	}
}

int main() {
	
	map<string,int> table;
	table["byr"] = 0;
	table["iyr"] = 0;
	table["eyr"] = 0;
	table["hgt"] = 0;
	table["hcl"] = 0;
	table["ecl"] = 0;
	table["pid"] = 0;
	table["cid"] = 0;

	string s;
	int valid = 0, counter = 0;
	string line;
	while (getline (cin, s)) {
	
		if (s.length() > 0) {
	
			for (unsigned int i = 0; i < s.length(); i++) {
				if (s[i] == ':')
					s[i] = ' ';
			}
			line = line + s + " ";

		} else {

			istringstream iss(line);
			string word, tmp;

			while (iss >> word >> tmp) {
				table[word]++;
				counter++;

				if (word == "cid") {
					counter--;
				}
				if (table[word] > 1) {
					counter = 0;
					clearMap(table);
					table[word]++;
				}
				if (counter == 7) {
					valid++;
					counter = 0;
					clearMap(table);
				}
			}

			counter = 0;
			line = "";
			clearMap(table);
		}
		
	}
	
	cout << valid << endl;
	return 0;
}