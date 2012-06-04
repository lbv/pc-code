#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int dim[101][3];

void adjust( int a[3] ) {
	int k = rand() % 10000;

	while( k-- ) {
		int i = rand() % 3;
		int j = rand() % 3;

		if( i != j ) {
			for( int l = 2; l <= a[i]; l++ ) {
				if( a[i] % l == 0 && a[j] * l <= 100 && rand() % 2 == 0 ) {
					a[i] /= l;
					a[j] *= l;
				}
			}
		}
	}
}

int main() {
	freopen("a.in", "w", stdout);

	int cases = 97;
	printf("%d\n", cases);
	while( cases-- ) {
		int n = rand() % 99 + 2;
		if( cases % 2 ) n = 100 - rand() % 10;

		if( cases == 20 ) n = 100;
		if( cases == 2 ) n = 2;

		printf("%d\n", n);

		int pp = rand() % 20 + 1;
		int qq = ( rand() % 20 + 1 ) * 3;
		int rr = ( rand() % 20 + 1 ) * 2;

		for( int i = 0; i < n; i++ ) {
			dim[i][0] = pp;
			dim[i][1] = qq;
			dim[i][2] = rr;

			adjust( dim[i] );
		}

		int give = rand() % 2;

		if( give ) {
			int xx, yy;
			while(1) {
				xx = rand() % n;
				yy = rand() % n;
				if( xx != yy ) break;
			}
			if( dim[xx][2] != 1 && dim[xx][2] != 100 ) {
				dim[yy][0] = dim[xx][0];
				dim[yy][1] = dim[xx][1];
				dim[yy][2] = dim[xx][2];

				dim[xx][2]--;
				dim[yy][2]++;

				adjust( dim[xx] );
				adjust( dim[yy] );
			}
		}


		for( int x = 0; x < n; x++ ) {
			char a[30];

			int len = rand() % 5 + 1;
			if( cases == 10 && x == n - 1 ) len = 20;
			for( int i = 0; i < len; i++ ) {
				a[i] = rand() % 26 + 97;
				if( rand() % 5 == 0 ) a[i] = rand() % 26 + 65;
				if( rand() % 30 == 0 ) a[i] = rand() % 10 + 48;
			}
			a[len] = 0;
			printf("%s %d %d %d\n", a, dim[x][0], dim[x][1], dim[x][2]);
		}
	}
	return 0;
}

