//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int MinMatrix[12][102] = {-1}; //Matrix with the minimal sum
int path[12][102] = {-1}; //Matrix with the direction for the minimal sum

int minimalSum(int mainValue, int options[], int row, int col, int TotalRows) { //Given three numbers, returns the minimal sum
	int min = 2000000, lexicographic = -1;
	for (int i = 0; i < 3; i++) {
		int sum = mainValue + options[i];
		if (sum < min) {
			min = sum;
			path[row][col] = i;
			lexicographic = i;
		} else if  (sum == min) { // If there are two values with minimalSum, check lexicographically
			if (row == 0 && lexicographic == 0) {	// Special case when row is 0
				lexicographic = i;
				path[row][col] = i;
			}
			else if (row == TotalRows - 1 && lexicographic < 2 && i == 2) { // Special case when row is last one
				lexicographic = i;
				path[row][col] = i;
			}
		}
	}
	return min;
}

int minValue(int row, int col, int TotalRows, int TotalCols) { // It actually return the value in the path matrix
	int result = path[row][col];
	return result-1;
}
void calculateMinPath(int m[][102], int row, int col) { // calculate the 3 possible values for a minimal sum
	if (col < 0)
		return;
	int j = col-1;
	for (int i = 0; i < row; i++) {
		path[i][j] = 0;
		int options[3];
		options[0] = MinMatrix[((i+row-1)%row)][j+1];
		options[1] = MinMatrix[i][j+1];
		options[2] = MinMatrix[((i+1)%row)][j+1];
		MinMatrix[i][j] = minimalSum(m[i][j],options, i, col-1, row);
	}
	calculateMinPath(m, row, col-1);
}

int getResult(int row, int col) { // Reads the minimal sum matrix and the path matrix and display the result
	int answer = 0;
	int smallest = 2000000, rowNum = 0;
	for (int i = 0; i < row; i++) {
		if (MinMatrix[i][0] < smallest) {
			smallest = MinMatrix[i][0];
			rowNum = i;
			answer = MinMatrix[i][0];
		}
	}
	cout << rowNum + 1;
	for (int j = 0; j < col - 1; j++) {
		int NewRowNum = 0;
		NewRowNum = minValue(rowNum, j, row, col);
		if (rowNum == 0) {
			if (NewRowNum == -1)
				rowNum = row - 1;
			else
				rowNum = rowNum + NewRowNum;
		}
		else if (rowNum == row -1) {
			if (NewRowNum == 1)
				rowNum = 0;
			else
				rowNum = rowNum + NewRowNum;
		} else {
			rowNum = rowNum + NewRowNum;
		}
		cout << " " << rowNum +1;
	}
	cout << endl;
	return answer;
}

int main() {
	int row = 0, col = 0;
	while ( cin >> row >> col) {
		int matrix[12][102];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> matrix[i][j];
				if (j == col - 1) {
					MinMatrix[i][j] = matrix[i][j];
					path[i][j] = 0;
				}
			}
		}
		int asnwer = 0;
		if (row == 1) { //Special Case when there is only one row
			cout << 1;
			asnwer += matrix[0][0];
			for (int i = 1; i < col; i++) {
				asnwer += matrix[0][i];
				cout << " " << 1;
			}
			cout << endl << asnwer << endl;
		} else {
			calculateMinPath(matrix, row, col-1);
			asnwer = getResult(row, col);
			cout << asnwer << endl;
		}
	}
}