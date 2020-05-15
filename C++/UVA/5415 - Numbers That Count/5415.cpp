//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

string ProcessNumber(string number) {
	int digits[10];
	string result;
	for (int i = 0; i < 10; i++){
		digits[i] = 0;
	}
	for (unsigned int i = 0; i < number.length(); i++) {
		digits[(int)number[i]-48]++;
	}
	for (int i = 0; i < 10; i++){
		if (digits[i] != 0) {
			result += to_string(digits[i]) + to_string(i);
		}
	}
	return result;
}

int main() {
	string originalNumber ;
	while (cin >> originalNumber && originalNumber != "-1") {
		string answer = ProcessNumber(originalNumber);
		vector<string> previousResults;
		vector<string>::iterator it;
		if (answer == originalNumber) {
			cout << originalNumber << " is self-inventorying" << endl;
		}
		else {
				for (int i = 1; i < 15; i++) {
					previousResults.push_back(answer);
					string newNumber = answer;
					answer = ProcessNumber(newNumber);
					it = find(previousResults.begin(), previousResults.end(), answer);
					if (answer == newNumber) {
						cout << originalNumber << " is self-inventorying after " << i << " steps" << endl;
						break;
					}
					else if (answer == originalNumber) {
						cout << originalNumber << " enters an inventory loop of length " << i + 1 << endl;
						break;
					}
					else if (it != previousResults.end()) {
						int index = distance(previousResults.begin(),it);
						cout << originalNumber << " enters an inventory loop of length " << i - index  << endl;
						break;
					}
					else if (i == 14) {
						cout << originalNumber << " can not be classified after 15 iterations" << endl;
						break;
					}
				}
		}
	}
}
