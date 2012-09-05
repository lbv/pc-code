#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

int main() {
	// freopen("g.in", "w", stdout);

	int cases = 195;

	printf("%d\n", cases);
	while( cases-- ) {
		int n;

		while(1) {
			n = rand() % 101;
			if( n >= 3 ) break;
		}
		if( cases == 30 ) n = 100;
		if( cases == 10 ) n = 3;

		int order[101];
		for( int i = 0; i < n; i++ ) {
			order[i] = i;
		}

		int x = rand() % 20000 + 10000;
		while( x-- ) {
			int p, q;

			p = rand() % n;
			q = rand() % n;
			swap( order[p], order[q] );
		}
		printf("\n%d\n", n);
		for( int i = 0; i < n; i++ ) {
			int j = (i + 1) % n;

			if( rand() % 2 ) printf("%d %d %d\n", order[i]+1, order[j]+1, rand() % 100 + 1);
			else printf("%d %d %d\n", order[j]+1, order[i]+1, rand() % 100 + 1);
		}
	}
	return 0;
}

