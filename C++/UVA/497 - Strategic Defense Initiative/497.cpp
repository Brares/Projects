//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int sasc_seq(int A[], int n, int S[]) // Function from the code library
{
  vector<int> last(n+1), pos(n+1), pred(n);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[pos[1] = 0];

  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    pred[i] = (j-1 > 0) ? pos[j-1] : -1;
    last[j] = A[pos[j] = i];
    len = max(len, j);
  }

  int start = pos[len];
  for (int i = len-1; i >= 0; i--) {
    S[i] = A[start];
    start = pred[start];
  }
  return len;
}

int main() {
	int n = 0;
	cin >> n;
	cin.clear();
	cin.ignore();
	string tmp;
	getline(cin, tmp);
	while (n--) {
		int number[200000], S[200000], counter = 0, k= 0, i = 0; // Choose 2,000,000 as the size of the array because I did not want to use MAX_INT
		getline(cin, tmp);
		number[counter] = stoi(tmp);
		while (true) {
			getline(cin, tmp);
			if (tmp.length() != 0) {
				counter++;
				number[counter] = stoi(tmp);
			} else {
				break;
			}
    	}
    	k = sasc_seq(number, counter+1, S);
	    cout << "Max hits: " << k << endl;
	    for (i = 0; i < k; i++) {
	      cout << S[i] << endl;
	    }
	    if (n > 0)
	    	cout << endl;
	}
}
