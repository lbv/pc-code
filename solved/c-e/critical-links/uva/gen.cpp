#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 15
#define MAXN 10000
#define MAXE 100000
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXE 30
#define NCRIT 2
#endif

#define Zero(v) memset(v, 0, sizeof(v))

bool g[MAXN][MAXN];
int T;

void test_case(bool crit = false)
{
	Zero(g);
	int n = crit ? MAXN : rand() % (MAXN + 1);

	printf("\n%d\n", n);
	if (n == 0) return;

	int MaxEdges = n;

	if (rand() % 3 == 0)
		MaxEdges = min(n + n/10, MAXE);
	if (rand() % 4 == 0)
		MaxEdges = min(n*(n-1)/2, MAXE);

	int e = rand() % (MaxEdges + 1);
	while (e--) {
		if (n == 1) break;

		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v);

		g[u][v] = true;
		g[v][u] = true;
	}

	for (int i = 0; i < n; ++i) {
		int ne = 0;
		for (int j = 0; j < n; ++j)
			if (g[i][j]) ++ne;

		printf("%d (%d)", i, ne);
		for (int j = 0; j < n; ++j)
			if (g[i][j]) printf(" %d", j);
		putchar('\n');
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
