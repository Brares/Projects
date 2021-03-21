// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int MaxNumber = 0;
int MinNumber = 10000;
int minRow, minCol, maxRow, maxCol;
vector<int>results;

int SearchRow(string line, int index, int low, int top) {
	if (index < 6) {
		int mid = (low + top) / 2;
		if (line[index] == 'F')
			return SearchRow(line, index+1, low, mid);
		else
			return SearchRow(line, index+1, mid+1, top);		
	}
	if (line[index] == 'F')
		return low;
	return top;
}

int SearchColumn(string line, int index, int left, int right) {
	if (index < 9) {
		int mid = (left + right) / 2;
		if (line[index] == 'L')
			return SearchColumn(line, index+1, left, mid);
		else
			return SearchColumn(line, index+1, mid+1, right);		
	}
	if (line[index] == 'L')
		return left;
	return right;
}

int missingNumber() {
	
	for (int i = minRow; i < maxRow; i++) {
		for (int j = 0; j < 8; j++) {
			int tmp = i * 8 + j;
			if (tmp > MinNumber && tmp < MaxNumber) {
				std::vector<int>::iterator it;
				it = std::find (results.begin(), results.end(), tmp); 
				if (it == results.end()) {
					return tmp;
				}
			}
		}
	}

	return -1;
}

int main() {

	string s;
	while (getline(cin, s)) {
		int low = 0, top = 127, left = 0, right = 7;
		int row = SearchRow(s, 0, low, top); 
		int col = SearchColumn(s, 7, left, right);
		int result = row * 8 + col;
		results.push_back(result);
		if (result > MaxNumber) {
			maxRow = row;
			maxCol = col;
			MaxNumber = result;
		}
		if (result < MinNumber) {
			minRow = row;
			minCol = col;
			MinNumber = result;
		}
	}

	cout << missingNumber() << endl;
	
	return 0;
}