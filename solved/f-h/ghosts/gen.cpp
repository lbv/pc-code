#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 1
#define MAXT 200
#define MAXN 25
#define MINN 5
#define MAXV 50
#endif

#if 0
#define MAXT 500
#define MAXN 25
#define MINN 5
#define MAXV 50
#endif


int T;
char board[MAXN][MAXN + 1];


void test_case()
{
	int n = rand() % (MAXN - (MINN-1)) + MINN;
	printf("\n%d\n", n);

	int p = rand() % 40 + 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			board[i][j] = (rand() % 100) < p ? '#' : '.';

		board[i][n] = 0;
	}

	int ng, nh;
	do {
		ng = rand() % MAXV + 1;
		nh = rand() % MAXV + 1;
		if (nh > ng) swap(ng, nh);
	} while (ng + nh >= n*n);

	for (int i = 0; i < ng; ++i) {
		int r, c;
		do {
			r = rand() % n;
			c = rand() % n;
		} while (board[r][c] == 'G');
		board[r][c] = 'G';
	}

	for (int i = 0; i < nh; ++i) {
		int r, c;
		do {
			r = rand() % n;
			c = rand() % n;
		} while (board[r][c] == 'G' || board[r][c] == 'H');
		board[r][c] = 'H';
	}

	for (int i = 0; i < n; ++i) printf("%s\n", board[i]);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) test_case();

	return 0;
}
