#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXCASES 10
#define MAXN 10000
#define MAXM 100000
#define MAXT 600
#define NCRIT 2
#endif

#if 1
#define MAXCASES 10
#define MAXN 10
#define MAXM 50
#define MAXT 600
#define NL 1
#define NCRIT 3
#endif


#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))


int T;

bool hotels[MAXN + 1];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
	int maxh = min(n, 100);
	int h = crit ? maxh : rand() % (maxh + 1);

	printf("%d\n%d", n, h);
	ClrN(hotels, n + 1, bool);
	while (h--) {
		int c;
		do {
			c = rand() % n + 1;
		} while (hotels[c]);
		hotels[c] = true;
		printf(" %d", c);
	}

	int m = crit ? MAXM : rand() % MAXM + 1;
	printf("\n%d\n", m);

	while (m--) {
		int u, v;
		do {
			u = rand() % n + 1;
			v = rand() % n + 1;
		} while (u == v);

		int t = rand() % MAXT + 1;

		printf("%d %d %d\n", u, v, t);
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXCASES;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();
	puts("0");

	return 0;
}
