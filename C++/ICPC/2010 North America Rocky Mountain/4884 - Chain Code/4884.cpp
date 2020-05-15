//Jonathan Flores

#include <bits/stdc++.h>

using namespace std;

int dx[] = {1,1,0,-1,-1,-1,0,1};
int dy[] = {0,-1,-1,-1,0,1,1,1};

struct Point {
  double x, y;
};

long long area_polygon(Point polygon[], int n)
{
  long long sum = 0;

  for (int i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return sum/2;
}

int main() {
	Point *polygon;
	string s;
	while(cin >> s) {
		long long x = 0, y = 0, a = 0, answer = 0;
		int size = s.length();
		polygon = new Point[size+1];
    	assert(polygon);

		polygon[0].x = x, polygon[0].y = y; // First Vertice
		for(int i = 0; i < size; i++) {
			int index = (int)s[i]-48;
			y = (y + dy[index]);
			x = (x + dx[index]);
			polygon[i+1].x = x, polygon[i+1].y = y; 
		}
		a = abs(area_polygon(polygon, size+1));
		answer += a + size/2 + 1 + a%2;
		//cout << "a: " << a << endl;
		cout << answer << endl;
    	delete[] polygon;
	}
}
