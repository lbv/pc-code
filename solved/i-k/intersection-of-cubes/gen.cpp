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
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


#if 0
#define MAXT 90
#define MAXN 100
#endif

#if 1
#define MAXT 25
#define MAXN 10
#endif


int cases, caseno, n;

int main() {
//	freopen("d.in", "w", stdout);

	srand(time(NULL));
	double cl = clock();
	int cases = MAXT;
	printf("%d\n", cases + 1);
	while( cases-- ) {
		n = rand() % MAXN + 1;

		//if( cases % 5 == 0 ) n = 100 - rand() % 5;
		//if( cases == 3 ) n = 100;

		printf("%d\n", n);
		int x1, y1, x2, y2, z1, z2;

		while(1) {
			x1 = rand() % 1000 + 1, x2 = rand() % 1000 + 1;
			if( x1 < x2 ) break;
		}
		while(1) {
			y1 = rand() % 1000 + 1, y2 = rand() % 1000 + 1;
			if( y1 < y2 ) break;
		}
		while(1) {
			z1 = rand() % 1000 + 1, z2 = rand() % 1000 + 1;
			if( z1 < z2 ) break;
		}

		if( cases == 8 ) {
			x1 = y1 = z1 = 1;
			x2 = y2 = z2 = 1000;
		}

		for( int i = 0; i < n; i++ ) {
			int xx, yy, zz;

			while(1) {
				xx = rand() % 1000 + 1;
				if( xx <= x1 ) break;
			}
			while(1) {
				yy = rand() % 1000 + 1;
				if( yy <= y1 ) break;
			}
			while(1) {
				zz = rand() % 1000 + 1;
				if( zz <= z1 ) break;
			}
			printf("%d %d %d ", xx, yy, zz);
			while(1) {
				xx = rand() % 1000 + 1;
				if( xx >= x2 ) break;
			}
			while(1) {
				yy = rand() % 1000 + 1;
				if( yy >= y2 ) break;
			}
			while(1) {
				zz = rand() % 1000 + 1;
				if( zz >= z2 ) break;
			}
			printf("%d %d %d\n", xx, yy, zz);
		}
	}
	printf("%d\n", MAXN);
	for( int i = 0; i < MAXN; i++ ) {
		int x1, y1, x2, y2, z1, z2;

		while(1) {
			x1 = rand() % 1000 + 1, x2 = rand() % 1000 + 1;
			if( x1 < x2 ) break;
		}
		while(1) {
			y1 = rand() % 1000 + 1, y2 = rand() % 1000 + 1;
			if( y1 < y2 ) break;
		}
		while(1) {
			z1 = rand() % 1000 + 1, z2 = rand() % 1000 + 1;
			if( z1 < z2 ) break;
		}
		printf("%d %d %d %d %d %d\n", x1, y1, z1, x2, y2, z2);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

