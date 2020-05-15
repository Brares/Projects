// Jonathan Flores

#include <bits/stdc++.h> 

using namespace std;

int main() {
	int k = 0;
	int e = 0;
	int counter = 0;
	vector<string> keyword;
	vector<string> excuses;
	while (cin >> k >> e) {
		int max = 0;
		vector<int> outputs;		
		counter++;
		keyword.clear();
		excuses.clear();
		for (int i = 0; i < k; i++) {
			string linek;
			cin >> linek;
			keyword.push_back(linek);
		}
		cin.clear(); // I was reading an extra empty line without this two lines of code 
		cin.ignore(201, '\n'); 
		for (int i = 0; i < e; i++) {
			int tmpCounter = 0;			
			string line;
			getline(cin, line);
			excuses.push_back(line);
			for (unsigned int j = 0; j < line.length(); j++) {
				if (!isalpha(line[j]))
					line[j] = ' ';
				else
					line[j] = tolower(line[j]);			
			}
			istringstream iss(line);
			string word;
			while(iss >> word) {				
				vector<string>::iterator it = find(keyword.begin(), keyword.end(), word);
				if (it != keyword.end()) {   	 				
					tmpCounter++;
				}
			}
			if (tmpCounter == max)
				outputs.push_back(i);
			else if (tmpCounter > max) {
				outputs.clear();
				max = tmpCounter;
				outputs.push_back(i);
			}
		}
		cout << "Excuse Set #" << counter << endl;
		for (int i = 0; i < outputs.size(); i++)
			cout << excuses[outputs[i]] << endl;
		cout << endl;
	}
	return 0;
}
