/*
	Author       :
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cmath>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

int main() {
	//freopen("e.in", "w", stdout);

    srand(time(NULL));
	int cases = 45;
	printf("%d\n", cases);
	while( cases-- ) {
		puts("");

		int m, n;

		while(1) {
			n = rand() % 201;
			if( n > 1 ) break;
		}
		if( cases % 10 == 0 ) n = 200;

		int A[1000];
		printf("%d\n", n);
		for( int i = 1; i <= n; i++ ) {
			if( i > 1 ) putchar(' ');
			A[i] = rand() % 20 + 1;
			A[1] = 1;
			printf("%d", A[i]);
		}
		puts("");

		m = rand() % (n*n) + 5*n;

		if( cases % 3 == 0 ) m = rand() % (n);

		set < pair <int, int> > S;
		while( m-- ) {
			int u, v;
			u = rand() % n + 1;
			v = rand() % n + 1;
			if( u != v ) {
				if( A[u] <= A[v] || ( cases % 10 == 0 && rand() % 100 == 2 ) )
				S.insert( make_pair( u, v ) );
			}
		}
		printf("%d\n", S.size());
		for( set < pair <int, int> >::iterator s = S.begin(); s != S.end(); s++ ) {
			printf("%d %d\n", s->first, s->second);
		}
		printf("%d\n", n - 1);
		for( int i = 2; i <= n; i++ ) printf("%d\n", i);
	}
	return 0;
}

