#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#define MAXT 5
#define MAXM 200000
#define MAXN 200000
#define MAXW 10000
#define NCRIT 2


typedef pair<int, int> II;


int T;
II edges[MAXN];


void gen(bool crit = false)
{
	int m = crit ? MAXM : rand() % MAXM + 1;
	int minn = m-1;
	int maxn = min(1LL * MAXN, 1LL * m*(m-1)/2);
	int n = crit ? maxn : rand() % (maxn - minn + 1) + minn;

	printf("%d %d\n", m, n);

	set<II> used;

	int ne = 0;
	for (int i = 1; i < m; ++i) {
		int u = i;
		int v = rand() % i;

		if (rand() % 2 == 0) swap(u, v);
		edges[ne++] = II(u, v);
		used.insert(II(u, v));
		used.insert(II(v, u));
		--n;
	}

	while (n--) {
		int u, v;
		do {
			u = rand() % m;
			v = rand() % m;
		} while (u == v || used.find(II(u, v)) != used.end());
		used.insert(II(u, v));
		used.insert(II(v, u));

		edges[ne++] = II(u, v);
	}

	random_shuffle(edges, edges + ne);
	for (int i = 0; i < ne; ++i) {
		int w = rand() % MAXW + 1;
		printf("%d %d %d\n", edges[i].first, edges[i].second, w);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	puts("0 0");

	return 0;
}
