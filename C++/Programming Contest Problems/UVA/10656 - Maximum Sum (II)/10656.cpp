//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 0;
	while (cin >> n && n) {
		int flag = 0;
		for (int i = 0; i < n; i++) {
			int num = 0;
			cin >> num;
			if(num != 0 && flag == 0) {
				flag = 1;
				cout << num;
			} else if (num != 0)
				cout << " " << num;
		}
		if (flag == 0)
			cout << "0" << endl;
		else
			cout << endl;
	}
	return 0;
}
