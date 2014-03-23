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

int main() {
	//freopen("coin1.in", "w", stdout);

    srand(time(NULL));
	double cl = clock();

	int cases = 97;
	printf("%d\n", cases);
	while( cases-- ) {
		int n = rand() % 50 + 1, K;

		if( cases % 10 ) n = 50 - rand() % 10;
		if( rand() % 3 ) n = 50;


		K = 1000 - rand() % 10;
		if( cases % 3 ) K = 1000;

		if( cases == 1  ) K = 1;
		if( cases == 2  ) K = 2;
		if( cases == 3  ) K = 3;

		if( cases == 5 || cases == 6 ) n = 1, K = 20;

		printf("%d %d\n", n, K);

		set <int> S;
		while( S.size() < n ) {
			if( cases == 5 || cases == 6 ) S.insert(5);
			else S.insert( rand() % 100 + 1 );
		}
		for( set <int> ::iterator s = S.begin(); s != S.end(); s++ ) {
			printf("%d ", *s);
		}
		for( int i = 0; i < n; i++ ) {
			if(i) putchar(' ');
			int k;
			if( cases == 5 ) k = 4;
			else if( cases == 6 ) k = 3;
			else k = rand() % 20 + 1;
			printf("%d", k);
		}
		puts("");
	}
	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

