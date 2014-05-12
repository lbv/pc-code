#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXN 1000
#define MAXK 300
#define MAXM 10000
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXK 9
#define MAXM 100
#define NL 1
#endif


void test_case()
{
	int N = rand() % MAXN + 1;
	int Lim = N < MAXK ? N : MAXK;
	int K = rand() % Lim + 1;

#if NL
	puts("");
#endif
	printf("%d %d\n", N, K);
	for (int i = 0; i <= N; ++i)
		printf("%d\n", rand() % MAXM + 1);
}

int main()
{
	srand(time(NULL));

	int T = MAXT;
	printf("%d\n", T);

	while (T--) test_case();

	return 0;
}
