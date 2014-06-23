#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 1
#define MAXN 500
#define MAXM 500
#define MAXP 1000000000
#define MAXQ 40000
#define NCRIT 1
#endif

#if 1
#define MAXT 1
#define MAXN 50
#define MAXM 50
#define MAXP 100
#define MAXQ 8
#define NCRIT 1
#endif


int T;


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int M = crit ? MAXM : rand() % MAXM + 1;

	printf("%d %d\n", N, M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (j > 0) putchar(' ');
			printf("%d", rand() % (MAXP + 1));
		}
		putchar('\n');
	}

	int Q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", Q);

	while (Q--) {
		int cmd = rand() % 2;

		if (cmd == 0) {
			int x1 = rand() % N + 1;
			int x2 = rand() % N + 1;
			int y1 = rand() % M + 1;
			int y2 = rand() % M + 1;

			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);

			printf("q %d %d %d %d\n", x1, y1, x2, y2);
		}
		else {
			int x = rand() % N + 1;
			int y = rand() % M + 1;
			int v = rand() % (MAXP + 1);

			printf("c %d %d %d\n", x, y, v);
		}
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
