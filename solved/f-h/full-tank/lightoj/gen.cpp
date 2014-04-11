#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 100
#define MAXM 1000
#define MAXF 100
#define MAXC 100
#define MAXW 100
#define MAXQ 100
#define NCRIT 1
#endif

#if 1
#define MAXT 20
#define MAXN 5
#define MAXM 10
#define MAXF 10
#define MAXC 10
#define MAXW 12
#define MAXQ 10
#define NCRIT 3
#define NL 1
#endif


int T;


void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
	int m = crit ? MAXM : rand() % (MAXM + 1);

	printf("%d %d\n", n, m);

	printf("%d", rand() % MAXF + 1);
	for (int i = 1; i < n; ++i)
		printf(" %d", rand() % MAXF + 1);
	putchar('\n');

	while (m--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v);

		int w = rand() % MAXW + 1;
		printf("%d %d %d\n", u, v, w);
	}

	int q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", q);
	while (q--) {
		int c = rand() % MAXC + 1;
		int s = rand() % n;
		int t = rand() % n;
		printf("%d %d %d\n", c, s, t);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
