// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<string> matrix;
	string s;
	while (getline(cin, s)) {
		matrix.push_back(s);
	}
	
	int indexRow = 0, indexCol = 0, tress = 0;
	unsigned int sizeCol = matrix.back().size();

	while (indexRow < matrix.size() - 1) {
		indexCol = ((indexCol + 3 ) % (sizeCol));
		if (matrix[++indexRow][indexCol] == '#')
			tress++;
	}

	/*for (int i = 0; i < matrix.size(); i++) {
		cout << matrix[i] << endl;
	}*/

	cout << tress << endl;
	return 0;
}