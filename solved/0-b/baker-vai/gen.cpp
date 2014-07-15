#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 25
#define MAXM 100
#define MAXN 100
#define MAXP 20
#define NCRIT 5
#endif

#if 1
#define MAXT 10
#define MAXM 16
#define MAXN 16
#define MAXP 20
#define NCRIT 2
#endif


int T;


void gen(bool crit = false)
{
	int m = crit ? MAXM : rand() % (MAXM - 1) + 2;
	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;

	printf("\n%d %d\n", m, n);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j > 0) putchar(' ');
			int p = rand() % (MAXP + 1);
			printf("%d", p);
		}
		putchar('\n');
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
