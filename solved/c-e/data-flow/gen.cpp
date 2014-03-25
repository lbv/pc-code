#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXN 100
#define MAXM 4000
#define MAXW 1000000000000000LL

#define Clr(m) memset(m, 0, sizeof(m))


typedef long long i64;


struct Edge {
	int u, v;
	i64 w;
	Edge() {}
	Edge(int U, int V, i64 W): u(U), v(V), w(W) {}
};


int T;

bool used[MAXN][MAXN];

Edge edges[MAXM];


i64 rand_i64()
{
	i64 r = rand();
	r <<= 32;
	r |= rand();
	return r;
}

Edge create_edge(int u, int v)
{
	if (rand() % 2 == 0) swap(u, v);
	i64 w = 0;

	int r = rand() % 100;
	if (r < 25)
		w = rand() % 100;
	else if (r < 50)
		w = rand() % 1000000;
	else
		w = rand_i64() % MAXW + 1;

	used[u][v] = used[v][u] = true;
	return Edge(u + 1, v + 1, w);
}

void test_case(bool crit = false)
{
	int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
	int maxm = min(MAXM, N*(N-1) / 2);
	int minm = N-1;

	int M = crit ? MAXM : rand() % (maxm - (minm-1)) + minm;

	printf("%d %d\n", N, M);

	Clr(used);
	int e = 0;
	for (int i = 1; i < N; ++i) {
		edges[e++] = create_edge(i, rand() % i);
		--M;
	}

	while (M--) {
		int u, v;
		do {
			u = rand() % N;
			v = rand() % N;
		} while (u == v || used[u][v]);
		edges[e++] = create_edge(u, v);
	}

	random_shuffle(edges, edges + e);

	for (int i = 0; i < e; ++i)
		printf("%d %d %lld\n", edges[i].u, edges[i].v, edges[i].w);

	int D = rand() % 100 + 1;
	int K = rand() % 100 + 1;

	printf("%d %d\n", D, K);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < 5; ++i) test_case(true);

	while (T) test_case();

	return 0;
}
