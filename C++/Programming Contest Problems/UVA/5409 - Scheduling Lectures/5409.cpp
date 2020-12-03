//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int totalLectures = 0;
int DI = 0;
int l= 0, c = 0, n = 0;
//int dp[1002][1002]= {0};
vector<vector<int>> dp2;

int CalculateDI(int t) {
	if (t == 0)
		return 0;
	else if (t <= 10)
		return -c;
	else
		return ((t - 10) * (t - 10));
}

int evaluate(int topic, int lecture, int topics[]) {
	if (lecture > totalLectures)
		return 2000000000; 	// Tried to used INT_MAX, but I got overflow
	if (topic >= n)
		return 0;
	//cout << "DP: " << dp[topic][lecture] << endl;
	if (dp2[topic][lecture] == 0) {
		int sum = 0, minimum = 2000000000;
		for (int i = topic; i < n; i++) {
            sum += topics[i];
            if (sum > l) 
            	break;
            minimum = min(minimum, CalculateDI(l-sum) + evaluate(i+1, lecture+1, topics));
        }
        dp2[topic][lecture] = minimum;
        //cout << dp[topic][lecture] << endl;
	}
	return dp2[topic][lecture];
}

int main() {
	n = 0;
	int index = 1;
	while(cin >> n && n) {
		if( index > 1)
			cout << endl;
		l = 0, c = 0;
		totalLectures = 1;
		cin >> l >> c;
		int* topics = new int[n];
		int sum = 0;
		for (int i = 0; i < n; i++){
			int tmp = 0;
			cin >> tmp;
			topics[i] = tmp;
			sum += tmp;
			if (sum > l) {
				totalLectures++;
				sum = tmp;
			}
		}
		dp2.clear();
		dp2.resize(n);
		for (int i = 0; i < n; i++) {
			dp2[i].clear();
			dp2[i].resize(n);
		}
		DI = evaluate(0, 0, topics);

		cout << "Case " << index++ << ":" << endl;
		cout << "Minimum number of lectures: " << totalLectures << endl;
		cout << "Total dissatisfaction index: " << DI << endl;

	}
}