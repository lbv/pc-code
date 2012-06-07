/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
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

#define NN 20001

#define MM 100002

int cases, caseno, n, team[NN], A[NN], B[NN];

struct dual {
	int x, y;
	bool operator < ( const dual &b ) const {
		if( x != b.x ) return x < b.x;
		return y < b.y;
	}
}E[MM];

int total, black;


set <int> L;

set <dual> S;

int main() {
	freopen("b.in","w",stdout);

	cases = 10;
	printf("%d\n", cases);
	srand(time(NULL));
	while( cases-- ) {
		int i, M;
		n = rand() % 100 + 1;

//		if( cases % 4 == 0 ) n = rand() % 100 + 1;

//		if( cases == 30 ) n = 100000;

		printf("%d\n", n);

		M = min( 20000, (rand() % 30 + 2) * n + 1 );

		for( i = 0; i < M; i++ ) {
			if(  (rand() + 17 * rand() ) % 2 == 0 ) team[i] = 0;
			else team[i] = 1;
		}

		int k = 0, l = 0;
		for( i = 0; i < M; i++ ) {
			if( !team[i] ) {
				A[k++] = i;
			}
			else B[l++] = i;
		}
		S.clear();
		while( n -- ) {
			dual a;

			while(1) {
				a.x = A[rand() % k];
				a.y = B[rand() % l];

				if( S.find(a) == S.end() ) {
					printf("%d %d\n", a.x + 1, a.y + 1);
					S.insert(a);
					break;
				}
			}
		}
	}
	return 0;
}

