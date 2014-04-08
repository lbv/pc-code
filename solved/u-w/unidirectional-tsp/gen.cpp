#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXM 10
#define MAXN 100
#define MAXI 1000000
#define MINI -1000000
#endif

#if 1
#define MAXT 20
#define MAXM 6
#define MAXN 15
#define MAXI 100
#define MINI -100
#define NL 1
#define NWDTH "4"
#endif

const int RangeI = MAXI - MINI + 1;


int T;


void test_case(bool crit = false)
{
	int m = crit ? MAXM : rand() % MAXM + 1;
	int n = crit ? MAXN : rand() % MAXN + 1;

#if NL
	puts("");
#endif
	printf("%d %d\n", m, n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			int num = rand() % RangeI + MINI;
			if (j > 0) putchar(' ');
#ifdef NWDTH
			printf("%" NWDTH "d", num);
#else
			printf("%d", num);
#endif
		}
		putchar('\n');
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < 5; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
