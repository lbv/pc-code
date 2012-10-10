#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <ctime>
using namespace std;

char a[30][30];

void placeChar( int m, int n, char c ) {
	while( 1 ) {
		int i = rand() % (m-2) + 1, j = rand() % (n-2) + 1;

		if( a[i][j] == '.' ) {
			a[i][j] = c;
			break;
		}
	}
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void placeObstacle( int m, int n ) {
	int i = rand() % (m-2) + 1, j = rand() % (n-2) + 1;

	if( a[i][j] != '.' ) return;

	if( rand() % 2 ) a[i][j] = 'm';
	else a[i][j] = '#';

	queue <int> Q;
	bool b[30][30] = {{0}};
	for( int x = 0; x < m; x++ ) for( int y = 0; y < n; y++ ) if( a[x][y] == 'h' ) {
		b[x][y] = true;
		Q.push(x);
		Q.push(y);
	}
	while( !Q.empty() ) {
		int x = Q.front();Q.pop();
		int y = Q.front();Q.pop();

		for( int k = 0; k < 4; k++ ) {
			int u = x + dx[k], v = y + dy[k];
			if( !b[u][v] && ( a[u][v] == '.' || a[u][v] == 'a' || a[u][v] == 'b' || a[u][v] == 'c' ) ) {
				b[u][v] = true;
				Q.push(u);
				Q.push(v);
			}
		}
	}
	int cnt = 0;
	for( int u = 0; u < m; u++ ) for( int v = 0; v < n; v++ ) if( (a[u][v] == 'a' || a[u][v] == 'b' || a[u][v] == 'c') && b[u][v] ) cnt++;
	if( cnt != 3 ) a[i][j] = '.';
}

int main() {
	//freopen("powerpuff.in", "w", stdout);
    srand(time(NULL));
	int cases = 95;
	printf("%d\n", cases);
	while(cases--) {
		int m = rand() % 17 + 4;
		int n = rand() % 17 + 4;

		if( cases % 3 ) m = 20 - rand() % 5, n = 20 - rand() % 5;

		if( cases == 5 ) m = n = 20;
		if( cases == 94 ) m = n = 4;

		printf("%d %d\n", m, n);
		for( int i = 0; i < m; i++ ) {
			for( int j = 0; j < n; j++ ) a[i][j] = '.';
			a[i][n] = 0;
		}
		for( int i = 0; i < m; i++ ) a[i][0] = a[i][n-1] = '#';
		for( int i = 0; i < n; i++ ) a[0][i] = a[m-1][i] = '#';

		placeChar( m, n, 'a' );
		placeChar( m, n, 'b' );
		placeChar( m, n, 'c' );
		placeChar( m, n, 'h' );

		int k = rand() % 1000;

		while( k-- ) {
			placeObstacle( m, n );
		}

		for( int i = 0; i < m; i++ ) puts(a[i]);
	}
	return 0;
}

