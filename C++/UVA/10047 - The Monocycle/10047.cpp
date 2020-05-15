//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int directionX[]= {-1,0,1,0};	// 4 Direction for X
int directionY[]= {0,1,0,-1};	// 4 Direction for Y

pair<int,int> startPoint, endPoint;

struct Node {
    int x, y, direction, colour, steps;
    Node(int x, int y, int d, int c, int e):
        x(x), y(y), direction(d), colour(c), steps(e) {}
};

int BFS(char matrix[28][28], int m, int n) {
	int answer = -1; //Default answer
	bool visited[28][28][4][5] = {};  //[x][y][dir][color] CURRENT STATE
	queue<Node> q;
	q.push(Node(startPoint.first, startPoint.second, 0, 0, 0));
	visited[startPoint.first][startPoint.second][0][0] = 1;

	int tmpX = 0, tmpY = 0; //Save tmp values
	while(!q.empty()) {
		Node tmpNode = q.front(); q.pop();
		if (tmpNode.x == endPoint.first && tmpNode.y == endPoint.second &&
			tmpNode.colour == 0){
			return answer = tmpNode.steps; // We got the answer. Each node save the steps from the beginning
		}
		tmpX = tmpNode.x + directionX[tmpNode.direction];
		tmpY = tmpNode.y + directionY[tmpNode.direction];

		//Move forward
		if (tmpX >= 0 && tmpY >= 0 && tmpX < m && tmpY < n && matrix[tmpX][tmpY] != '#') {
			int tmpColour = (tmpNode.colour + 1) % 5;
			if (visited[tmpX][tmpY][tmpNode.direction][tmpColour] == 0){
				visited[tmpX][tmpY][tmpNode.direction][tmpColour] = 1;
				q.push(Node(tmpX, tmpY, tmpNode.direction, tmpColour, tmpNode.steps + 1));
			}
		}

		tmpX = tmpNode.x;
		tmpY = tmpNode.y;

		//Turn Left
		int tmpDirection = (tmpNode.direction + 3) % 4;
		if (visited[tmpX][tmpY][tmpDirection][tmpNode.colour] == 0){
			visited[tmpX][tmpY][tmpDirection][tmpNode.colour] = 1;
			q.push(Node(tmpX, tmpY, tmpDirection, tmpNode.colour, tmpNode.steps+1));
		}

		//Turn Right
		tmpDirection = (tmpNode.direction + 1) % 4;
		if (visited[tmpX][tmpY][tmpDirection][tmpNode.colour] == 0){
			visited[tmpX][tmpY][tmpDirection][tmpNode.colour] = 1;
			q.push(Node(tmpX, tmpY, tmpDirection, tmpNode.colour, tmpNode.steps+1));
		}
	}
	return answer;
}

int main() {
	int m = 0, n = 0, cases = 1;

	while (cin >> m >> n && m && n) {
		if (cases != 1)
			cout << endl;
		char matrix[28][28];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matrix[i][j];
				if(matrix[i][j] == 'S')
					startPoint = make_pair(i,j);
				else if (matrix[i][j] == 'T')
					endPoint = make_pair(i,j);
			}
		}
		int answer = BFS(matrix, m, n);
		cout << "Case #" << cases++ << endl;
		if (answer == -1)
			cout << "destination not reachable" << endl;
		else
			cout << "minimum time = " << answer << " sec" << endl;
	}
}
