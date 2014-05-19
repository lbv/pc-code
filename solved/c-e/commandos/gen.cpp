#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 100
#endif

#if 1
#define MAXT 20
#define MAXN 4
#define NL 1
#endif


#define Zero(v) memset((v), 0, sizeof(v))


int T;
bool g[MAXN][MAXN];


void test_case(bool crit = false)
{
#if NL
	puts("");
#endif
	int N = rand() % (MAXN - 1) + 2;
	if (crit) N = MAXN;
	printf("%d\n", N);

	int MaxR = N * (N - 1) / 2;
	int R;
	do {
		R = rand() % (MaxR + 1);
	} while (R < N - 1);
	printf("%d\n", R);

	Zero(g);

	for (int i = 1; i < N; ++i) {
		int u = rand() % i;
		int v = i;
		g[u][v] = g[v][u] = true;
		printf("%d %d\n", u, v);
		--R;
	}

	while (R--) {
		int u, v;
		do {
			u = rand() % N;
			v = rand() % N;
		} while (u == v || g[u][v]);

		g[u][v] = g[v][u] = true;
		printf("%d %d\n", u, v);
	}

	int s = rand() % N;
	int d = rand() % N;
	printf("%d %d\n", s, d);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	test_case(true);
	while (T) test_case();

	return 0;
}
