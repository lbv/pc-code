#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXR 100
#define MAXC 100
#define MAXQ 100
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXR 8
#define MAXC 8
#define MAXQ 10
#define NCRIT 2
#define NL 1
#endif


int T;


void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

	int R = crit ? MAXR : rand() % MAXR + 1;
	int C = crit ? MAXC : rand() % MAXC + 1;
	printf("%d %d\n", R, C);
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j)
			putchar(rand() % 2 == 0 ? '0' : '1');
		putchar('\n');
	}

	int Q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", Q);

	while (Q--) {
		int x = rand() % (2*R + 1);
		int y = rand() % (2*C + 1);
		printf("%d %d\n", x, y);
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
