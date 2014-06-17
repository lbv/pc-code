#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 1
#define MAXT 70
#define MAXN 1000
#define MAXM 10000
#define FIXED 1
#define NCRIT 5
#endif

#if 0
#define MAXT 20
#define MAXN 8
#define MAXM 16
#define NCRIT 3
#endif

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool g[MAXN][MAXN];


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int maxm = min(MAXM, N * (N-1) / 2);
	int M = crit ? maxm : rand() % (maxm + 1);

	printf("\n%d %d\n", N, M);
	Clr(g);
	while (M--) {
		int u, v;
		do {
			u = rand() % N;
			v = rand() % N;
		} while (u == v || g[u][v]);
		g[u][v] = true;

		printf("%d %d\n", u+1, v+1);
	}

	--T;
}

void gen_fixed()
{
	int N = MAXN;
	int M = N - 1;
	printf("\n%d %d\n", N, M);

	for (int i = 1; i <= M; ++i)
		printf("%d %d\n", i, i+1);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

#if FIXED
	gen_fixed();
#endif

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
