#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define NN 105
#define MM 12005

int cases, caseno, n, m;

int main() {
	freopen("c.in", "w", stdout);
	cases = 95;
	printf("%d\n", cases);
	while( cases-- ) {
		n = rand() % 100 + 1;
		m = rand() % (12000 - 3);


		if( cases == 20 ) n = 100, m = 12000 - 3;
		if( cases == 15 ) n = 1;
		if( cases == 30 ) n = 100;

		if( n < 100 && m > n * n ) m = rand() % (n * n);

		printf("\n%d\n", n);
		for( int i = 1; i <= n; i++ ) {
			int u = rand() % i;
			int w = rand() % 10000 + 1;
			printf("%d %d %d\n", u, i, w);
			m--;
		}
		if( m > 0 ) {
			n++;
			while( m-- ) {
				int u, v;
				while( 1 ) {
					u = rand() % n;
					v = rand() % n;
					if( u != v ) break;
				}
				printf("%d %d %d\n", u, v, rand() % 10000 + 1);
			}
		}
		puts("0 0 0");
	}
	return 0;
}

