#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 200
#define MAXBUSY 20
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 16
#define MAXBUSY 20
#define NL 1
#define NCRIT 3
#endif

#define Clr(m) memset(m, 0, sizeof(m))


int T;

bool g[MAXN][MAXN];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d", n);

	for (int i = 0; i < n; ++i) {
		int busy = rand() % MAXBUSY + 1;
		printf(" %d", busy);
	}
	putchar('\n');

	int minr = n-1;
	int maxr = n*(n-1)/2;
	int r = rand() % (maxr - minr + 1) + minr;

	printf("%d\n", r);

	Clr(g);
	while (r--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || g[u][v]);
		g[u][v] = true;

		printf("%d %d\n", u+1, v+1);
	}

	int q = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", q);

	while (q--) {
		int u = rand() % n;
		printf("%d\n", u + 1);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
