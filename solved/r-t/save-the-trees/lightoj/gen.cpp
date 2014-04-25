#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 5
#define MAXN 200000
#define MAXTYPE 200000
#define MAXH 200000
#define NCRIT 2
#endif

#if 0
#define MAXT 10
#define MAXN 1000
#define MAXTYPE 100
#define MAXH 10000
#define NCRIT 3
#define NL 1
#endif


int T;


void test_case(bool crit = false)
{
#if NL
	puts("");
#endif
	int N = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", N);

	while (N--) {
		int t = rand() % MAXTYPE + 1;
		int h = rand() % MAXH + 1;
		printf("%d %d\n", t, h);
	}

	--T;
}

void test_crit1()
{
	int N = MAXN;
	printf("%d\n", N);

	while (N--) {
		int t = 1;
		int h = MAXH;
		printf("%d %d\n", t, h);
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	// test_crit1();
	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
