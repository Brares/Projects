//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

struct DNA{
	int sum;
	int id;
};

bool operator<(const DNA &j1, const DNA&j2)
{
	if (j1.sum  != j2.sum)
    	return j1.sum  < j2.sum;
    return j1.id < j2.id;
}

int calculateSum(string s, int m) {
	int sum = 0;
	for (int i = 0; i < m; i++) {
		for (int j = i+1; j < m; j++) {
			if (s[i] > s[j]){ 
				sum++;
			}		
		}
	}
	return sum;
}
int main() {
	int m = 0;
	cin >> m;
	while(m--) {
		int length = 0, numberLines = 0;
		cin >> length >> numberLines;
		string* lines = new string[numberLines];
		int* sums = new int[numberLines];
		vector<DNA> dns;
		for (int i = 0; i < numberLines; i++) {
			cin >> lines[i];
			sums[i] = calculateSum(lines[i], length);
			DNA tmp = {sums[i], i};
			dns.push_back(tmp);
		}
		sort(dns.begin(), dns.end());
		for (int i = 0; i < numberLines; i++) {
			cout << lines[dns[i].id] << endl;
		}
		if(m != 0)
			cout << endl;
	}
}