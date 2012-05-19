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

int getRandom( int cases ) {
	int k;
	while(1) {
		k = rand() % 32767 + 1;
		if( cases == 20 ) {
			if( k >= 30000 ) break;
		}
		else if( cases == 30 ) {
			if( k <= 100 ) break;
		}
		else if( cases == 40 ) {
			if( k <= 10 ) break;
		}
		else break;
	}
	return k;
}

int main() {
	freopen("e.in", "w", stdout);

	double cl = clock();

	int cases = 50;

	printf("%d\n", cases);
	while( cases-- ) {
		int n = 100 - rand() % 10;

		if( cases % 5 == 0 ) n = 100;
		if( cases <= 3 ) n = cases + 1;

		printf("%d\n", n);
		for( int i = 0; i < n; i++ ) {
			for( int j = 0; j <= i; j++ ) {
				if( j ) putchar(' ');
				printf("%d", getRandom(cases));
			}
			puts("");
		}
		for( int i = 0; i < n - 1; i++ ) {
			for( int j = 0; j < n - i - 1; j++ ) {
				if( j ) putchar(' ');
				printf("%d", getRandom(cases));
			}
			puts("");
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

