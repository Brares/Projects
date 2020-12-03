//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int to;
  int gas;
  int weight;       // can be double or other numeric type
  Edge(int t, int g, int w)
    : to(t), gas(g), weight(w) { }
  bool operator < (const Edge &that) const {
    return weight > that.weight;
  }
};
  
typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new vector<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int g, int weight)
  {
    nbr[u].push_back(Edge(v, g, weight));
    nbr[v].push_back(Edge(u, g, weight));
  }
};

/* assume that D have been allocated */
int dijkstra(const Graph &G, int src, int goal, int D[][100], 
			int capacity, int fuelPrice[]) {
  int result = -1;
  int n = G.num_nodes;
  priority_queue<Edge> fringe;

  for (int i = 0; i < n; i++)
  	for (int j = 0; j <= capacity; j++)
  		D[i][j] = INT_MAX;

  D[src][0] = 0;
  fringe.push(Edge(src,0,0));

  while (!fringe.empty()) {
    Edge next = fringe.top();
    fringe.pop();
    int u = next.to;
    if (u == goal)
    	return next.weight;
    if (D[u][next.gas] < next.weight) continue;

    if (next.gas < capacity && next.weight + fuelPrice[u] < D[u][next.gas+1]){
      D[u][next.gas+1] = next.weight + fuelPrice[u];
      fringe.push(Edge(u, next.gas+1, next.weight + fuelPrice[u]));
    }

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int distance = it->weight;
      if (next.gas >= distance) {
      	int tmpGas = next.gas - distance;
      	if (next.weight < D[v][tmpGas]) {
      		D[v][tmpGas] = next.weight;
			fringe.push(Edge(v,tmpGas,next.weight));
      	}
      }
    }
  }
  return result;
}

int main() {
	int n = 0, m = 0;
	cin >> n >> m;
	int fuelPrice[1000];
	for (int i = 0; i < n; i++) {
		cin >> fuelPrice[i];
	}

	Graph G(m);
	
	for (int i = 0; i < m; i++) {
		int u = 0, v = 0, w = 0;
		cin >> u >> v >> w;
		G.add_edge(u,v,0,w);
	}

	int q = 0;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int c = 0, s = 0, e = 0;
		int D[10000][100];
		cin >> c >> s >> e;

		int result = dijkstra(G,s,e,D,c, fuelPrice);
		if ( result != -1) {
			cout << result << endl;	
		} else {
			cout << "impossible" << endl;
		}
 	}
}
