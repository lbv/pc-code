#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;


#if 0
#define MAXT 100
#define MAXC 100
#define MAXS 1000
#define MAXQ 10000
#define MAXD 1000
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXC 5
#define MAXS 8
#define MAXQ 5
#define MAXD 100
#define NCRIT 1
#define NL 1
#endif


#define Clr(m) memset(m, 0, sizeof(m))


bool used[MAXC + 1][MAXC + 1];
int T;


void test_case(bool crit = false)
{
	int C = crit ? MAXC : rand() % (MAXC - 1) + 2;

	int MaxS = min(MAXS, C * (C-1) / 2);
	int S = crit ? MaxS : rand() % MaxS + 1;

	int Q = crit ? MAXQ : rand() % (MAXQ + 1);

#if NL
	puts("");
#endif
	printf("%d %d %d\n", C, S, Q);

	Clr(used);
	while (S--) {
		int c1, c2;
		do {
			c1 = rand() % C + 1;
			c2 = rand() % C + 1;
		} while (c1 == c2 || used[c1][c2]);
		used[c1][c2] = used[c2][c1] = true;

		int d = rand() % MAXD + 1;
		printf("%d %d %d\n", c1, c2, d);
	}

	while (Q--) {
		int c1, c2;
		do {
			c1 = rand() % C + 1;
			c2 = rand() % C + 1;
		} while (c1 == c2);

		printf("%d %d\n", c1, c2);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	puts("0 0 0");

	return 0;
}
