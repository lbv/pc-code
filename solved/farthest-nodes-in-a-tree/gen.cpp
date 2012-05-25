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

#define NN 30000

int edges[30002][2];

int main() {
	freopen("a.in", "w", stdout);

	double cl = clock();

	int cases = 8;
	printf("%d\n", cases + 2);
	while( cases-- ) {
		int n = rand() % (NN - 1) + 2;
		if( cases != 2 ) n = NN;

		for( int i = 1; i < n; i++ ) {
			edges[i-1][0] = i;
			edges[i-1][1] = rand() % i;

			if( cases == 4 && i > 200 && n > 1000 && rand() % 50 == 0 ) {
				edges[i-1][1] = rand() % 100 + 100;
			}
		}
		int k = rand() % 200000;
		while( k-- ) {
			int i = rand() % (n - 1);
			int j = rand() % (n - 1);
			swap( edges[i][0], edges[j][0] );
			swap( edges[i][1], edges[j][1] );
		}
		k = rand() % 200000;
		while( k-- ) {
			int i = rand() % (n - 1);
			swap( edges[i][0], edges[i][1] );
		}
		printf("%d\n", n);
		for( int i = 0; i < n - 1; i++ ) printf("%d %d %d\n", edges[i][0], edges[i][1], rand() % 10000 + 1);
	}
	printf("%d\n", NN);
	for( int i = NN - 2; i >= 0; i-- ) {
		printf("%d %d %d\n", i, i + 1, rand() % 10000 + 1);
	}
	printf("%d\n", NN);
	for( int i = 1; i < NN; i++ )
		printf("0 %d %d\n", i, rand() % 10000 + 1);
	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

