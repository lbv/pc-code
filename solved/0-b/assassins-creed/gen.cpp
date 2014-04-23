#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 50
#define MAXN 15
#define MAXM 50
#define NCRIT 8

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool adj[MAXN][MAXN];


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
	int maxm = min(MAXM, n * (n-1) / 2);

	int m = crit ? maxm : rand() % (maxm + 1);

	printf("\n%d %d\n", n, m);

	Clr(adj);
	while (m--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || adj[u][v]);
		adj[u][v] = true;

		printf("%d %d\n", u + 1, v + 1);
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
