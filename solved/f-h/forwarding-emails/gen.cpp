#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 20
#define MAXN 50000
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define NCRIT 3
#define NL 1
#endif


typedef pair<int, int> II;


int T;
II conn[MAXN];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
	printf("%d\n", N);

	for (int i = 1; i <= N; ++i) {
		int j;
		do {
			j = rand() % N + 1;
		} while (j == i);
		conn[i-1] = II(i, j);
	}
	random_shuffle(conn, conn + N);

	for (int i = 0; i < N; ++i)
		printf("%d %d\n", conn[i].first, conn[i].second);

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
