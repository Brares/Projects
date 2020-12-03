//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

const int MAX_LEN = 126;

int LCS(string A, int n, string B, int m)
{
  int L[MAX_LEN+1][MAX_LEN+1];
  int i, j;
  
  for (i = n; i >= 0; i--) {
  	for (j = m; j >= 0; j--) {
      if (i == n || j == m) {
      	L[i][j] = 0;
      } 
      else if (A[i] == B[j]) {
      		L[i][j] = 1 + L[i+1][j+1];
      } 
      else {
      	L[i][j] = max(L[i+1][j], L[i][j+1]);
      }
    }
  }
  
  return L[0][0];
}

int main() {
	string line1;
	int counter = 1;
	while(getline(cin,line1) && line1!= "#") {
		string line2;
		getline(cin,line2);
  		int m = 0, n = 0, l = 0;
  		n = line1.length();
  		m = line2.length();

		l = LCS(line1, n, line2, m);
    	
    	cout << "Case #" << counter++ << ": you can visit at most " << l << " cities." << endl;
	}
	
}