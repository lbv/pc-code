#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 15
#define MAXN 10000
#define MAXM 100000
#define NCRIT 3
#endif

#if 0
#define MAXT 30
#define MAXN 15
#define MAXM 10
#define NCRIT 1
#endif


int T;


void test_case(bool crit = false)
{
	int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
	int M = crit ? MAXM : rand() % (MAXM + 1);

	printf("\n%d %d\n", N, M);
	while (M--) {
		int u, v;
		do {
			u = rand() % N + 1;
			v = rand() % N + 1;
		} while (u == v);

		printf("%d %d\n", u, v);
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
