/*
	Author       :	Jan
	Problem Name :	Athletics Track
	Algorithm    :	Math Geometry Bisection
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

int caseno, cases;

void genCase( int n, int m, int A ) {
	printf("%d %d %d\n", n, m, A);
	while( m-- ) {
		int u, v;

		while(1) {
			u = rand() % n + 1;
			v = rand() % n + 1;
			if( u != v ) break;
		}
		printf("%d %d %d\n", u, v, rand() % 10000 + 1);
	}
}

int main() {
	//freopen("j.in", "w", stdout);

	srand(time(NULL));
	int cases = 11;

	printf("%d\n", cases + 4);
	while( cases-- ) {
		int n = rand() % 1000 + 1;
		int m = rand() % 10001;
		int A = rand() % 10000 + 1;

		if( n == 1 ) m = 0;
		genCase( n, m, A );
	}
	genCase( 1, 0, 1000 );
	genCase( 10000, 100000, 100 );
	genCase( 10000, 100000, 100 );
	genCase( 10000, 0, 100 );
	return 0;
}

