// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

bool solvable(double d, int AP, int house[100001], int NumHouses) {
	int counter =  1;
	double location = house[0] + d; // Location of the first AP
	for (int i = 0; i < NumHouses; i++) {
		if (location + d >= house[i]) {
				continue;
		}
		else {
			location = house[i] + d; // We put the next AP
			counter++;
		}
		if (counter > AP){
			return false;
		}
	}
	return true;
}
int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		int AP = 0, NumHouses = 0;
		cin >> AP >> NumHouses;
		int house[100001];
		for (int i = 0; i < NumHouses; i++) {
			cin >> house[i];
		}
		sort(house, house + NumHouses);
		double low = 0, high = house[NumHouses-1] - house[0];
    if (AP >= NumHouses) {
			low = 0.0;
			high = -1;
		}
		while ((high - low) > 0.01) {
			double mid = ((low + high)/2.00);
			if (solvable(mid, AP, house, NumHouses)) {
				high = mid;
			} else {
				low = mid;
			}
		}
		double answer = low;
		cout << fixed << setprecision(1) << answer << endl;
	}
	return 0;
}
