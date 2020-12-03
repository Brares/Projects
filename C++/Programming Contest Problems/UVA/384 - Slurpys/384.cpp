//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

bool slump(string s, int start, int end) {
	int index = start, size = s.size();

	if (index == size)
		return false;
	if (s[index] == 'D' || s[index] == 'E')
		index++;
	else
		return false;
	if (index == size)
		return false;
	if (s[index] == 'F')
		index++;
	else
		return false;
	if (index == size)
		return false;
	while (s[index] == 'F')
		index++;
	if (s[index] == 'G' && index == end)
				return true;
	else 
		return slump(s, index, end);

	return false;
}

bool slimp(string s, int start, int end) {
	int index = start, size = s.size();

	if (index == size)
		return false;
	if (s[index] == 'A')
		index++;
	else
		return false;
	if (index == size)
		return false;
	if (s[index] == 'H' && index == end)
		return true;
	if (s[end] != 'C')
		return false;
	if (s[index] == 'B') {
		index++;
		return slimp(s, index,end-1);
	}
	else {
		return slump(s, index, end-1);
	}
	return false;
}

int main() {
	int n = 0;
	cin >> n;
	cout << "SLURPYS OUTPUT" << endl;
	while(n--) {
		string line;
		cin >> line;
		int size = line.size();
		bool flag = false;
		for (int i = 0; i < size; i++) {
			if (line[i] == 'H' || line[i] == 'C') {
				if (slimp(line, 0, i) && slump(line, i+1, size-1)) {
					flag = true;
					break;
				}
			}		
		}
		if(flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	cout << "END OF OUTPUT" << endl;
}