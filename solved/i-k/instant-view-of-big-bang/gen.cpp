#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 125
#define MAXN 1000
#define MAXM 2000
#define MINW -1000
#define MAXW 1000
#define NCRIT 8
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define MAXM 8
#define MINW -100
#define MAXW 100
#define NCRIT 1
#endif

const int RangeW = MAXW - MINW + 1;

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool used[MAXN][MAXN];


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;

	int MaxM = min(MAXM, n * (n-1));
	int m = crit ? MaxM : rand() % (MaxM + 1);

	printf("\n%d %d\n", n, m);

	Clr(used);
	while (m--) {
		int u, v, w;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || used[u][v]);
		used[u][v] = true;

		w = rand() % RangeW + MINW;
		printf("%d %d %d\n", u, v, w);
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
