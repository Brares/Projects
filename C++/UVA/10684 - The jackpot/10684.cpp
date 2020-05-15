//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int vecsum(int v[], int n, int &start, int &end) // Function from the Code Library
{
  int maxval = 0;
  int max_end = 0;
  int max_end_start, max_end_end;
  int i;

  start = max_end_start = 0;
  end = max_end_end = -1;
  for (i = 0; i < n; i++) {
    if (v[i] + max_end >= 0) {
      max_end = v[i] + max_end;
      max_end_end = i;
    } else {
      max_end_start = i+1;
      max_end_end = -1;
      max_end = 0;
    }

    if (maxval < max_end) {
      start = max_end_start;
      end = max_end_end;
      maxval = max_end;
    } else if (maxval == max_end) {
      if (max_end_end - max_end_start > end - start ||
          (max_end_end - max_end_start == end - start &&
           max_end_start < start)) {
        start = max_end_start;
        end = max_end_end;
        maxval = max_end;
      }
    }
  }
  return maxval;
}

int main() {
	int cases = 0;
	while(cin >> cases && cases) {
		int number[10001];
		int sum, start, end;
		for (int i = 0; i < cases; i++) {
			cin >> number[i];
		}
		sum = vecsum(number, cases, start, end);
		if(sum != 0)
			cout << "The maximum winning streak is " << sum << "." << endl;
		else
			cout << "Losing streak." << endl;
	}
}
