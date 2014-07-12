#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 1000
#define MAXN 1000
#define MAXP 100
#define MAXW 30
#define MAXG 100
#define NCRIT 10
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXP 100
#define MAXW 30
#define MAXG 6
#define NCRIT 2
#define NL 1
#endif


int T;


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int N = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", N);

	while (N--) {
		int P = rand() % MAXP + 1;
		int W = rand() % MAXW + 1;
		printf("%d %d\n", P, W);
	}

	int G = crit ? MAXG : rand() % MAXG + 1;
	printf("%d\n", G);

	while (G--) {
		int MW = rand() % MAXW + 1;
		printf("%d\n", MW);
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
