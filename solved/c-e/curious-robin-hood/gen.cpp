#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define MAXV 1000
#define NCRIT 2
#endif

#if 1
#define MAXT 10
#define MAXN 16
#define MAXQ 8
#define MAXV 100
#define NCRIT 2
#define NL 1
#endif


int T;


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int n = crit ? MAXN : rand() % MAXN + 1;
	int q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d %d\n", n, q);

	for (int i = 0; i < n; ++i) {
		if (i > 0) putchar(' ');
		int v = rand() % (MAXV + 1);
		printf("%d", v);
	}
	puts("");

	for (int i = 1; i < q; ++i) {
		int t = rand() % 3;
		if (t == 0)
			printf("1 %d\n", rand() % n);
		else if (t == 1)
			printf("2 %d %d\n", rand() % n, rand() % MAXV + 1);
		else {
			int j = rand() % n;
			int i = rand() % (j + 1);
			printf("3 %d %d\n", i, j);
		}
	}
	printf("3 0 %d\n", n - 1);

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
