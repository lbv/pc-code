#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 30
#define MAXN 10000
#define MAXM 20000
#define MAXK 10000
#define MAXD 10
#define MAXW 1000
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define MAXM 8
#define MAXK 6
#define MAXD 3
#define MAXW 100
#define NCRIT 3
#define NL 1
#endif


typedef pair<int, int> II;


int T;


void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
	int maxm = min(MAXM, n * (n-1) / 2);
	int m = crit ? maxm : rand() % (maxm + 1);
	int maxk = min(MAXK, n * (n-1) / 2);
	int k = crit ? maxk : rand() % (maxk + 1);
	int d = crit ? MAXD : rand() % (MAXD + 1);

	printf("%d %d %d %d\n", n, m, k, d);

	set<II> rs;
	while (m--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || rs.find(II(u, v)) != rs.end());
		rs.insert(II(u, v));
		int w = rand() % MAXW + 1;
		printf("%d %d %d\n", u, v, w);
	}

	rs.clear();
	while (k--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || rs.find(II(u, v)) != rs.end());
		rs.insert(II(u, v));
		int w = rand() % MAXW + 1;
		printf("%d %d %d\n", u, v, w);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
