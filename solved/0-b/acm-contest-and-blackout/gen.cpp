#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 15
#define MAXN 100
#define MAXM 10000
#define MAXC 300
#define NCRIT 3
#endif

#if 1
#define MAXT 15
#define MAXN 100
#define MAXM 10000
#define MAXC 300
#define NCRIT 10
#endif


#define Clr(m) memset(m, 0, sizeof(m))


int T;


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % (MAXN - 2) + 3;
	int M = rand() % (MAXM - N + 1) + N;

	printf("%d %d\n", N, M);

	for (int i = 1; i < N; ++i) {
		int u = i;
		int v = rand() % i;

		if (rand() % 2 == 0) swap(u, v);
		int w = rand() % MAXC + 1;

		printf("%d %d %d\n", u+1, v+1, w);
		--M;
	}

	while (M--) {
		int u, v;
		do {
			u = rand() % N;
			v = rand() % N;
		} while (u == v);
		int w = rand() % MAXC + 1;

		printf("%d %d %d\n", u+1, v+1, w);
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
