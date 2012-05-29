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
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int cases, save[50000][2];
int cap[101][101];

int main() {
	freopen("e.in", "w", stdout);

	cases = 45;
	printf("%d\n", cases);
	while( cases-- ) {
		int n = rand() % 100 + 1;

		if( rand() % 4 ) n = rand() % 30 + 1;

		if( cases == 20 ) n = 100;

		bool road[102][102] = {0};

		for( int i = 1; i < n; i++ ) {
			int k = rand() % i;
			road[i][k] = road[k][i] = true;
		}

		int m = rand() % 100;
		if( cases % 3 == 0 ) m = 0;
		while( m-- ) {
			int u = rand() % n;
			int v = rand() % n;
			if( u == v || road[u][v] ) continue;

			road[u][v] = road[v][u] = true;
		}

		m = 0;
		for( int i = 0; i < n; i++ ) for( int j = i + 1; j < n; j++ ) if( road[i][j] ) m++;

		printf("%d\n", n);
		printf("%d\n", m);
		for( int i = 0; i < n; i++ ) for( int j = i + 1; j < n; j++ ) if( road[i][j] ) {
			if( rand() % 2 ) printf("%d %d\n", i, j);
			else printf("%d %d\n", j, i);
		}

		int s = rand() % n;
		int d = rand() % n;

		printf("%d %d\n", s, d);
	}
	return 0;
}

