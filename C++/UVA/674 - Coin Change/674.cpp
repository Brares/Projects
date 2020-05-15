//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int denom[5] = {1,5,10,25,50};
int previousResults[8000][5];

int RecursiveFunction(int sum, int n) {
  if (sum == 0 ) {
      return 1;
  }
  if (n < 0)
    return 0;
  if (previousResults[sum][n] != 0)
    return previousResults[sum][n];
  int result = 0, iterations = sum / denom[n];
  for (int i = 0; i <= iterations; i++) {
    int newSum = sum - (i*denom[n]);
    result += RecursiveFunction(newSum, n-1);
  }
  return previousResults[sum][n] = result;
}
int main() {
	int change = 0;
  while (cin >> change) {
    int result = 0;
    result = RecursiveFunction(change, 4);
    cout << result << endl;
  }
}
