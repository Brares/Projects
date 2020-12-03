// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use

      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	    }
	    else {
	       uf[res1].p = res2;
	       if (uf[res1].rank == uf[res2].rank) {
		  uf[res2].rank++;
	       }
	    }
	    return true;
	 }
	 return false;
      }

   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {     // recursive funcion for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

int main() {
	int n = 0, copy = 0;
	cin >> n;
	copy = n;
	string s;
	getline(cin,s);
	while (n--) {
		if (copy != n+1)
			cout << endl;
		int computers = 0;
		int good = 0;
		int bad = 0;
		cin >> computers;
		getline(cin,s);
		UnionFind unionData(computers+1);
		while (getline(cin,s), s != "")	{
			stringstream ss(s);
			char c;
			int a, b;
			ss >> c >> a >> b;
			if (c == 'c') {
				unionData.merge(a,b);
			}
			else {
				if (unionData.find(a) == unionData.find(b))
					good++;
				else
					bad++;
			}
		}
		cout << good << "," << bad << endl;
	}
}
