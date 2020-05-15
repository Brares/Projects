//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;
double roads = 0.0;
double rails = 0.0;
int states = 0;

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

      int find(UF uf[], int x) {             // for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int i=-1, int j=-1, int weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      int w;            /* weight, can be double instead of int */
};

void mst(int n, int m, Edge elist[], int index[], int& size, bool isRail[], int r)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      if (elist[i].w > (r * r)) {
      	rails += sqrt(elist[i].w);
      	states++;
      }
      else
      	roads += sqrt(elist[i].w);
      uf.merge(c1, c2);
    }
  }
}

int main() {
	cout << fixed << setprecision(0);
	int t = 0, counter = 1;
	cin >> t;
	while( t--) {
		int n = 0, r = 0;
		cin >> n >> r;
    int* x = new int[n];
    int* y = new int[n];
    int* index = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> x[i] >> y[i];
		}

    Edge* elist = new Edge[n*n];
    bool* isRail = new bool[n*n];
    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        elist[k++] = Edge(i,j,(((x[j]-x[i])*(x[j]-x[i])) + ((y[j]-y[i])*(y[j]-y[i]))));
      }
    }
    int t;  // number of edges in the mst
    roads =0.0, rails = 0.0, states = 1;
    mst(n, k, elist, index, t, isRail, r);
    if (counter-1 != t)
      cout << "Case #" << counter << ": " << states << " " << roads << " " << rails << endl;
    else
      cout << "Case #" << counter << ": " << states << " " << roads << " " << rails;
    counter++;
	}
}
