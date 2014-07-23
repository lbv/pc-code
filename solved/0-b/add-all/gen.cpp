#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 5000
#define MAXI 100000
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 16
#define MAXI 1000
#define NCRIT 3
#endif


int T;


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
	printf("%d\n", N);

	for (int i = 0; i < N; ++i) {
		if (i > 0) putchar(' ');
		int x = rand() % MAXI + 1;
		printf("%d", x);
	}
	putchar('\n');

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	puts("0");

	return 0;
}
