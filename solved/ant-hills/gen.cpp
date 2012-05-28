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
#include <vector>
#include <cassert>
#include <set>

using namespace std;

int cases, pr[10005];

int findPr( int u ) {
	if( u == pr[u] ) return u;
	return pr[u] = findPr(pr[u]);
}

set < pair <int, int> > S;

int main() {
	freopen("d.in", "w", stdout);

	int cases = 20;
	printf("%d\n", cases);
	while( cases-- ) {
		puts("");

		int n = rand() % 20 + 1;

		if( cases < 5 ) n = rand() % 5000 + 5000;

		if( cases == 2 ) n = 10000;


		S.clear();


		for( int i = 0; i < n; i++ ) pr[i] = i;

		int taken = 0;
		while( n != 1 ) {
			int u = rand() % n;
			int v = rand() % n;

			int xx = findPr(u);
			int yy = findPr(v);
			if( xx == yy ) continue;
			pr[yy] = xx;
			taken++;
			S.insert( make_pair( min(u, v), max(u, v) ) );
			if( taken == n - 1 ) break;
		}
		int k = rand() % (n);

		while( k-- ) {
			int u = rand() % n;
			int v = rand() % n;
			if( u > v ) swap( u, v );

			if( u == v ) continue;

			if( S.find( make_pair(u, v) ) == S.end() )  S.insert( make_pair(u, v) );
		}
		printf("%d %d\n", n, S.size());
		for( set < pair<int, int> > ::iterator s = S.begin(); s != S.end(); s++ ) {
			if( rand() % 2 ) printf("%d %d\n", s->first + 1, s->second + 1);
			else printf("%d %d\n", s->second + 1, s->first + 1);
		}
	}

	return 0;
}

