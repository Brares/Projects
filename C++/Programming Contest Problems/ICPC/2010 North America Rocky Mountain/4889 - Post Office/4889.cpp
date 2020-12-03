//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<double> tmp;
	double num1, num2, num3;
	while (cin >> num1 >> num2 >> num3 && num1 && num2 && num3) {
		tmp.push_back(num1);
		tmp.push_back(num2);
		tmp.push_back(num3);
		sort(tmp.begin(), tmp.end());
		double thickness = tmp[0];
		double height = tmp[1];
		double length = tmp[2];
		tmp.clear();

		//cout << thickness << " " << height << " " << length << endl;

		if (length >= 125 && height >= 90 && thickness >= 0.25) {
			if (length <= 290 && height <= 155 && thickness <= 7)
				cout << "letter" << endl;
			else if (length <= 380 && height <= 300 && thickness <= 50)
				cout << "packet" << endl;
			else if (length + height + height + thickness + thickness <= 2100 )
				cout << "parcel" << endl;
			else
				cout << "not mailable" << endl;

		} else {
			cout << "not mailable" << endl;
		}
	}
}
