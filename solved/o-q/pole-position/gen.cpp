#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 20
#define MAXN 1000
#define MAXC 10000
#define MINP -1000000
#define MAXP 1000000
#define NCRIT 3
#endif

#if 1
#define MAXT 10
#define MAXN 8
#define MAXC 100
#define MINP -10
#define MAXP 10
#define NCRIT 1
#endif


#define Clr(m) memset(m, 0, sizeof(m))


const int RangeP = MAXP - MINP + 1;


int T;
int cs[MAXN];
int ps[MAXN];
int used[MAXC+1];


void test_ok(bool crit = false)
{
	int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
	printf("%d\n", N);

	Clr(used);
	for (int i = 0; i < N; ++i) {
		int C;
		do {
			C = rand() % MAXC + 1;
		} while (used[C]);
		used[C] = true;
		cs[i] = C;
		ps[i] = i;
	}

	random_shuffle(ps, ps + N);

	for (int i = 0; i < N; ++i)
		printf("%d %d\n", cs[i], ps[i] - i);

	--T;
}

void test_case()
{
	int N = rand() % (MAXN - 1) + 2;
	printf("%d\n", N);

	Clr(used);
	for (int i = 0; i < N; ++i) {
		int C;
		do {
			C = rand() % MAXC + 1;
		} while (used[C]);
		used[C] = true;
		cs[i] = C;
		ps[i] = rand() % RangeP + MINP;
	}

	for (int i = 0; i < N; ++i)
		printf("%d %d\n", cs[i], ps[i]);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) test_ok(true);
	while (T) {
		int r = rand() % 10;
		if (r < 6) test_ok();
		else test_case();
	}

	puts("0");

	return 0;
}
