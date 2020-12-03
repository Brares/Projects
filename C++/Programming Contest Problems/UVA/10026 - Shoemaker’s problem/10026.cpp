//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

struct Job
{
    int time;
    int fine;
    int id;
};

bool operator<(const Job &j1, const Job&j2)
{
    return j1.time * j2.fine < j2.time * j1.fine;
}

int main() {
	int cases = 0;
	cin >> cases;
	while (cases--) {
		int n = 0;
		cin >> n;
		vector<Job> jobs;
		for (int i = 0; i < n; i++) {
			int time = 0, fine = 0;
			cin >> time >> fine;
			Job tmp = {time,fine,i+1};
			jobs.push_back(tmp);
		}
		sort(jobs.begin(), jobs.end());
		for (int i = 0; i < n; i++) {
			if(i != 0)
				cout << " " << jobs[i].id;
			else
				cout << jobs[i].id;
		}
		cout << endl;
		if(cases != 0)
			cout << endl;
	}
}
