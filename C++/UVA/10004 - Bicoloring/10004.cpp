//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;
string answer = "BICOLORABLE.";
bool flag = false;

class Graph {
    int V;

    list<int> *adj;
    int colour[200];

    public:
    Graph(int V);

    void addEdge(int v, int w);

    void DFS(int v);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
    colour[v] = 0;
    colour[w] = 0;
}

void Graph::DFS(int v) {
  string answer = "BICOLORABLE.";
  bool *visited = new bool[V];
  stack<int> stack;
  stack.push(v);

  while (!stack.empty()) {
    v = stack.top(); stack.pop();

    if (!visited[v]) {
      visited[v] = true;
      if (colour[v] == 0)
        colour[v] = 1;
    }

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
      if (colour[*i] == 0 && colour[v] == 2) {
        colour[*i] = 1;
      } else if (colour[*i] == 0 && colour[v] == 1)
        colour[*i] = 2;
      if (!visited[*i])
            stack.push(*i);
      else if (visited[*i] == true && colour[v] == colour[*i])
          answer = "NOT BICOLORABLE.";
    }
  }
  cout << answer << endl;
}

int main() {
	int n = 0;
	while( cin >> n && n) {
		int l = 0;
		cin >> l;
		Graph g(n);
		for (int i = 0; i < l; i++) {
			int a = 0, b = 0;
			cin >> a >> b;
			g.addEdge(a,b);
		}
		g.DFS(0);
	}
}
