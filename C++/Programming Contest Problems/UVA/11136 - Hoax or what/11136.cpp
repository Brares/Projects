// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
  long long n;
	while (cin >> n && n) {
    multiset <long long, greater <long long> > data;
    map<long long, long long> table;
    long long total = 0;
    while (n--) {
      long long k;
      cin >> k;
      while (k--) {
        long long bill;
        cin >> bill;
        data.insert(bill);
	++table[bill];
      }
      long long max = *data.begin();
      long long low = *data.rbegin();
      total += (max - low);
      --table[max];
      --table[low];
      if (table[max] <= 0 )
	data.erase(max);
      if (table[low] <= 0)
	data.erase(low);
    }
    cout << total << endl;
  }
	return 0;
}
