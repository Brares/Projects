// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int countTrees(int increaseCol, int increaseRow, vector<string> matrix) {
	
	int indexRow = 0, indexCol = 0, trees = 0;
	unsigned int sizeCol = matrix.back().size();

	while (indexRow < matrix.size() - 1) {
		
		indexCol = ((indexCol + increaseCol ) % (sizeCol));
		indexRow += increaseRow;

		if (matrix[indexRow][indexCol] == '#')
			trees++;
	}

	return trees;
}
int main() {
	vector<string> matrix;
	string s;
	while (getline(cin, s)) {
		matrix.push_back(s);
	}
	
	long long trees = 1;
	trees *= countTrees(1,1, matrix);
	trees *= countTrees(3,1, matrix);
	trees *= countTrees(5,1, matrix);
	trees *= countTrees(7,1, matrix);
	trees *= countTrees(1,2, matrix);


	cout << trees << endl;
	return 0;
}