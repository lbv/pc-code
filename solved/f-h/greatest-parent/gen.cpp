#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define MAXV 2000000000
#define NCRIT 1
#endif

#if 1
#define MAXT 2
#define MAXN 32
#define MAXQ 3
#define MAXV 10000
#define NCRIT 2
#endif


int T;
int ss[MAXN];


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int q = crit ? MAXQ : rand() % MAXQ + 1;

	if (N == 1) q =0;
	printf("\n%d %d\n", N, q);

	for (int i = 1; i < N; ++i) {
		int p = rand() % i;
		ss[i] = rand() % MAXV + 1;
		printf("%d %d\n", p, ss[i]);
	}

	while (q--) {
		int k = rand() % (N-1) + 1;
		int v = rand() % ss[k] + 1;
		printf("%d %d\n", k, v);
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
