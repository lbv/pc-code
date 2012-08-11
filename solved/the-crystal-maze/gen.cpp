/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int NN = 505;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

char a[NN][NN];
int cnt, m, n, q;

void printWall( int x, int y ) {
	if( !cnt ) return;
	cnt--;
	a[x][y] = '#';
	int k = rand() % 4;
	int u = x + dx[k];
	int v = y + dy[k];

	if( u >= 0 && u < m && v >= 0 && v < n ) printWall( u, v );
}

int main() {
	// freopen("a.in", "w", stdout);

    srand(time(NULL));
	double cl = clock();

	int cases = 10;
	printf("%d\n", cases);
	while( cases-- ) {
		m = 500, n = 500, q = 1000;
//		m = 50, n = 50, q = 100;

		printf("%d %d %d\n", m, n, q);
		for( int i = 0; i < m; i++ ) {
			for( int j = 0; j < n; j++ ) {
				a[i][j] = '.';
				if( rand() % 4 && cases >= 5 ) a[i][j] = 'C';
				else if( rand() % 3 == 0 ) a[i][j] = 'C';
			}
			a[i][n] = 0;
		}
		if( cases != 2 ) {
			for( int i = 0; i < 100; i++ ) {
				cnt = rand() % 10000 + 1;
				printWall( rand() % m, rand() % n );
			}
		}
		for( int i = 0; i < m; i++ ) puts(a[i]);
		while(q--) {
			while(1) {
				int x = rand() % m;
				int y = rand() % n;
				if( a[x][y] == '.' ) {
					printf("%d %d\n", x + 1, y + 1);
					break;
				}
			}
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

