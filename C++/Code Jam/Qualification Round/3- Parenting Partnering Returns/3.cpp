//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

struct task {
	int start;
	int end;
	int id;
	char person;
};

bool sortStart(const task &j1, const task &j2) {
	if (j1.start == j2.start)
		return j1.end < j2.end;
    return j1.start < j2.start;
}

bool sortID(const task &j1, const task &j2) {	
    return j1.id < j2.id;
}

int main() {
	int cases = 0;
	cin >> cases;
	int counter = 1;
	while (cases--) {
		string answer = "";
		vector<task> tasks;
		int n = 0;
		cin >> n;
		
		for (int i = 0; i < n; i++) {
			int start = 0, end= 0;
			cin >> start >> end;
			task tmp = {start, end, i, ' '};
			tasks.push_back(tmp);
		}
		
		sort(tasks.begin(), tasks.end(), sortStart); // Sort by start time and end time
		
		/*for(int i = 0; i < n; i++) {
			cout << tasks[i].start << " " << tasks[i].end << endl;
		}*/

		bool flag1 = true, flag2 = true;
		int time1 = 0, time2 = 0;
		for(int i = 0; i < n; i++) {
			if (time1 <= tasks[i].start) {
				flag1 = true;
			}
			if (time2 <= tasks[i].start) {
				flag2 = true;
			}
			if (flag1 == false && flag2 == false) {
				answer = "IMPOSSIBLE";
				break;
			}
			if (flag1 == true) {
				tasks[i].person = 'C';
				flag1 = false;
				time1 = tasks[i].end;
				continue;
			}
			if (flag2 == true) {
				tasks[i].person = 'J';
				flag2 = false;
				time2 = tasks[i].end;
				continue;
			}
		}
		sort(tasks.begin(), tasks.end(), sortID);
		
		cout << "Case #" << counter++;
		if (answer != "IMPOSSIBLE") {
			cout << ": ";
			for(int i = 0; i < n; i++) {
				cout << tasks[i].person; 
			}
			cout << endl;
		} else {
			cout << ": " << answer << endl;
		}
		
	}
	return 0;
}