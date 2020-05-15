//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

/* maximum number of nodes, maximum degree, and maximum number of edges */
const int MAX_N = 1000;
const int MAX_DEG = 4;

// vector of pair to save the answers. It sorted at the end
vector<pair<int,int>>answer;

struct Node {
  int deg;
  int nbrs[MAX_DEG];
  int dfs, back;
};

int dfn;

void clear_graph(Node G[], int n) {
	int i;
  	for (i = 0; i < n; i++) {
    	G[i].deg = 0;
  	}
}

void add_edge(Node G[], int u, int v) {
	G[u].nbrs[G[u].deg++] = v;
	G[v].nbrs[G[v].deg++] = u;
}

void do_dfs(Node G[], int v, int pred, stack<int> &v_stack, stack<int> &w_stack) {
	int i, w, child = 0;

	G[v].dfs = G[v].back = ++dfn;
	for (i = 0; i < G[v].deg; i++) {
    	w = G[v].nbrs[i];
    	if (G[w].dfs < G[v].dfs && w != pred) {
      		v_stack.push(v);
      		w_stack.push(w);
    	}
    	if (!G[w].dfs) {
      		do_dfs(G, w, v, v_stack, w_stack);
      		child++;
      		if (G[w].back >= G[v].dfs) {
				vector<pair<int,int>>tmp;
				while (v_stack.top() != v || w_stack.top() != w) {
	  				tmp.push_back(make_pair(v_stack.top() + 1, w_stack.top() + 1));
	  				v_stack.pop();
	  				w_stack.pop();
				}
				tmp.push_back(make_pair(v_stack.top() + 1, w_stack.top() + 1));
				v_stack.pop();
				w_stack.pop();

				if (tmp.size() == 1) {
					answer.push_back(make_pair(tmp[0].first, tmp[0].second));
					answer.push_back(make_pair(tmp[0].second, tmp[0].first));
				} else {
					for (unsigned int i = 0; i < tmp.size(); i++){
						answer.push_back(make_pair(tmp[i].first, tmp[i].second));
					}
				}
      		} else {
				G[v].back = min(G[v].back, G[w].back);
      		}
    	} else {
      		G[v].back = min(G[v].back, G[w].dfs);
    	}
  	}
}

void bicomp(Node G[], int n) {
	int i;
  	stack<int> v_stack, w_stack;

  	dfn = 0;
  	for (i = 0; i < n; i++) {
    	G[i].dfs = 0;
  	}
  	do_dfs(G, 0, -1, v_stack, w_stack);
}

int main() {
	Node G[MAX_N];
	int m = 0, n = 0;
	int counter = 1;
	while (cin >> n >> m && n && m) {
		answer.clear();
		clear_graph(G, n);
		cout << counter++ << endl << endl;
		for (int i = 0; i < m; i++) {
			int a = 0, b = 0;
			cin >> a >> b;
			add_edge(G, a-1, b-1);
		}
		bicomp(G, n);
		sort(answer.begin(), answer.end());
		for(unsigned int i = 0; i < answer.size(); i++) {
			cout << answer[i].first << " " << answer[i].second << endl;
		}
		cout << "#" << endl;
	}
}