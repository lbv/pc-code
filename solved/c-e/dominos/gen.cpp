#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT 10
#define MAXN 100000
#define MAXM 100000
#define NCRIT 3
#endif

#if 0
#define MAXT 5
#define MAXN 100000
#define MAXM 10000
#define NCRIT 3
#endif


typedef pair<int, int> II;


int T;


void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
	int maxm = min(1LL*n*(n-1)/2, 1LL*MAXM);
	int m = crit || maxm == 0 ? maxm : rand() % maxm + 1;

	printf("%d %d\n", n, m);

	set<II> used;
	while (m--) {
		int u, v;
		do {
			u = rand() % n + 1;
			v = rand() % n + 1;
		} while (u == v || used.find(II(u, v)) != used.end());
		used.insert(II(u, v));

		printf("%d %d\n", u, v);
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
