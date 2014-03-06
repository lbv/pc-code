/*
	Author       :	Jan
	Problem Name :	Fire!
	Algorithm    :	BFS
	Complexity   :
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

#define inf 1000000000

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int cases, m, n, val[1002][1002], v[1002][1002], caseno;
char a[1002][1002];

struct pos {
	int x, y;
	pos() {}
	pos( int xx, int yy ) { x = xx, y = yy; }
}st;

queue <pos> Q;

bool valid( int x, int y ) {
	if( x >= 0 && x < m && y >= 0 && y < n ) {
		return a[x][y] == '.';
	}
	return false;
}

char grid[205][205];

int main() {
	freopen("f.in", "w", stdout);

	int cases = 49;
	printf("%d\n", cases + 1);
	srand(time(NULL));
	while( cases-- ) {

	
		int m = rand() % 200 + 1;
		int n = rand() % 200 + 1;


/*
    	int m = rand() % 10 + 1;
		int n = rand() % 10 + 1;
*/


		if( cases % 4 ) {
			m = 200 - rand() % 50;
			n = 200 - rand() % 50;
		}
		if( cases % 10 == 0 ) m = n = 200;


		printf("%d %d\n", m, n);
		for( int i = 0; i < m; i++ ) {
			for( int j = 0; j < n; j++ ) grid[i][j] = '.';
			grid[i][n] = 0;
		}
		for( int i = 0; i < m; i++ ) {
			for( int j = 0; j < n; j++ ) {
				if( rand() % 10 == 0 ) grid[i][j] = '#';
				if( cases % 12 == 0 && rand() % 10 == 0 ) grid[i][j] = 'F';
			}
		}
		int k;
		while(1) {
			k = rand() % 10 ;
			if( k * 10 <= m * n ) break;
		}
		while( k-- ) {
			int x = rand() % m;
			int y = rand() % n;
			grid[x][y] = 'F';
		}

		int x = rand() % m;
		int y = rand() % n;
		grid[x][y] = 'J';

		for( int i = 0; i < m; i++ ) puts(grid[i]);
	}

	int m, n;
	m = n = 200;

	for( int i = 0; i < m; i++ ) {
		for( int j = 0; j < n; j++ ) {
			grid[i][j] = '.';
			if( rand() % 10 == 0 ) grid[i][j] = '#';
		}
		grid[i][n] = 0;
	}
	for( int i = 0; i < n; i++ ) if( rand() % 5 == 0 ) grid[100][i] = '#';
	for( int i = 101; i < m; i++ ) for( int j = 0; j < n; j++ ) grid[i][j] = 'F';

	int x = rand() % 100;
	int y = rand() % n;
	grid[x][y] = 'J';

	printf("%d %d\n", m, n);

	for( int i = 0; i < m; i++ ) puts(grid[i]);
	return 0;
}

