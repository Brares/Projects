//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;

  Edge(int t, int c, bool real = true)
    : to(t), cap(c), flow(0), is_real(real)
  {};

  int residual() const
  {
    return cap - flow;
  }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new list<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap)
  {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow)
{
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
		    vector<bool> &visited, int step = 0)
{
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1) {
	return it->residual();
      } else if (flow > 0) {
	return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t)
{
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);

  return flow;
}

int main() {
	int t = 0;
	cin >> t;
	vector<string> names, parties, clubs; // The index of the vectors is the ID for name, party and club

  	string emptyLine;
  	getline(cin, emptyLine);
  	getline(cin, emptyLine);

	while (t--) {
		string line;
		names.clear(); parties.clear(); clubs.clear();
    	vector<vector<int>> namesToClub;
    	int namesToParty[1000];
		while (getline(cin, line)) {
     			
     			if(line.empty()) break;
				
				string name, party, club;
				stringstream ss(line);

				ss >>  name >> party;
				names.push_back(name);

      			vector<string>::iterator it;
      			it = find(parties.begin(), parties.end(), party);
				if (it == parties.end()) { // If the new party is not part of the vector, we added it.
					parties.push_back(party);
        			namesToParty[names.size() -1] = parties.size() - 1;
				} else {
          			namesToParty[names.size() -1] = distance(parties.begin(),it);
      			}
      			
      			vector<int> tmp;
				while (ss >> club) {
        			it = find(clubs.begin(), clubs.end(), club);
					if (it == clubs.end()) {
						clubs.push_back(club);
          				tmp.push_back(clubs.size()-1);
					} else {
          				tmp.push_back(distance(clubs.begin(),it));
        			}
				}
      			namesToClub.push_back(tmp);
		}

    	int numClubs = clubs.size();
    	int numNames = names.size();
    	int numParties = parties.size();
    	int end = 1 + numClubs + numNames + numParties;

    	Graph G(1 + numClubs + numNames + numParties + 1);
    	for (int i = 0; i < numClubs; i++) { 	// Edges from Source to Clubs
      		G.add_edge(0, 1 + i, 1);
    	}
    	for (int i = 0; i < numNames; i++) {
      		for (unsigned int j = 0; j < namesToClub[i].size(); j++) { 	// Edges from Clubs to Names
        		G.add_edge(1 + namesToClub[i][j],1 + numClubs + i,1);
      		}
      		G.add_edge(1 + numClubs + i,1 + numClubs + numNames + namesToParty[i],1); 	// Edges from Names to Parties
    	}
    	for (int i = 0; i < numParties; i++) {
    		G.add_edge(1 + numClubs + numNames + i, end, (numClubs -1)/2);	// Edges from Parties to Sink	
    	}

    	int maxFlow = network_flow(G, 0, end);
    	//cout << "MaxFlow:" << maxFlow << endl;

    	vector<pair<int,int>>answer;
    	if(maxFlow != numClubs) {
    		cout << "Impossible." << endl;
    	} else {
    		for (int i = 1; i <= numClubs; i++) {
    			for (EdgeIter it = G.nbr[i].begin(); it != G.nbr[i].end(); ++it) {
    				int v = it->to;
    				int flow = it->flow;
    				if (flow != 0 && it->is_real == true) {
    					answer.push_back(make_pair(v - numClubs - 1, i-1)); 	// Get the Flow, make pairs with the answer 
    				}
  				}
    		}
    		sort(answer.begin(), answer.end());
			for(unsigned int i = 0; i < answer.size(); i++) {
				cout << names[answer[i].first] << " " << clubs[answer[i].second] << endl;	// Get the answer
			}
    	}
    	if(t != 0)
    		cout << endl;
	}
}