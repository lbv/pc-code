#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 8
#define MAXN 100000
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define NL 1
#endif

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)


bool vis[MAXN*2 + 1];
bool dist[MAXN*2 + 1];

int bh[MAXN];
int rh[MAXN];


void fill_hooks(int *h, int n, int top)
{
	Clr(vis);

	for (int i = 0; i < n; ++i) {
		int j;
		do {
			j = rand() % top + 1;
		} while (vis[j]);

		vis[j] = true;
		h[i] = j;
	}
}

void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	int m = crit ? MAXN : rand() % MAXN + 1;
	printf("%d %d\n", n, m);

	int top = n+m;

	Clr(bh);
	fill_hooks(bh, n, top);
	sort(bh, bh + n);

	Clr(rh);
	fill_hooks(rh, m, top);
	sort(rh, rh + m);

	Clr(dist);
	for (int i = 0; i < n; ++i)
		dist[i] = true;

	random_shuffle(dist, dist + top);

	int j = 0;
	for (int i = 0; i < top; ++i)
		if (dist[i])
			printf("%d %d\n", i + 1, bh[j++]);

	j = 0;
	for (int i = 0; i < top; ++i)
		if (! dist[i])
			printf("%d %d\n", i + 1, rh[j++]);
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
