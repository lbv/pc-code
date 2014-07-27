#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 50
#define MAXM 50
#define MAXW 1200
#define MAXC 100000
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXM 12
#define MAXW 16
#define MAXC 1000
#define NCRIT 2
#define NL 1
#endif


#define Zero(v) memset((v), 0, sizeof(v))


int T;
bool vis[MAXM][MAXM];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int M = crit ? MAXM : rand() % (MAXM - 1) + 2;
	int MaxW = min(MAXW, M*(M-1) / 2);
	int W = crit ? MAXW : rand() % (MaxW + 1);

	printf("%d %d\n", M, W);
	for (int i = 2; i < M; ++i) {
		if (i > 2) putchar(' ');
		int c = rand() % (MAXC + 1);
		printf("%d", c);
	}
	puts("");

	Zero(vis);
	while (W--) {
		int i, j;
		do {
			i = rand() % M;
			j = rand() % M;
		} while (i == j || vis[i][j]);

		vis[i][j] = vis[j][i] = true;
		int c = rand() % (MAXC + 1);
		printf("%d %d %d\n", i + 1, j + 1, c);
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
