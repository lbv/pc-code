#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 5
#define MAXN 50000
#define MAXM 100000
#define MAXD 10000
#define MAXQ 50000
#endif

#if 0
#define MAXT 20
#define MAXN 10
#define MAXM 15
#define MAXD 100
#define MAXQ 10
#endif


void test_case(bool crit=false)
{
	int N = crit ? MAXN : rand() % (MAXN-1) + 2;
	int M = crit ? MAXM : rand() % (MAXM - (N - 2)) + (N - 1);

	printf("%d %d\n", N, M);

	int x, y, d;
	for (int i = 2; i <= N; ++i) {
		y = i;
		x = rand() % (y - 1) + 1;
		d = rand() % MAXD + 1;

		printf("%d %d %d\n", x, y, d);
		--M;
	}

	while (M--) {
		do {
			x = rand() % N + 1;
			y = rand() % N + 1;
		} while(x == y);
		d = rand() % MAXD + 1;
		printf("%d %d %d\n", x, y, d);
	}

	int q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", q);
	while (q--) {
		int s, t;
		do {
			s = rand() % N + 1;
			t = rand() % N + 1;
		} while (s == t);
		printf("%d %d\n", s, t);
	}
}

int main()
{
	srand(time(NULL));

	int T = MAXT;
	printf("%d\n", T);

	test_case(true); --T;

	while (T--) test_case();

	return 0;
}
