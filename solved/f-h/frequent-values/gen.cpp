#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 8
#define MAXN 100000
#define MAXQ 100000
#define MINA -100000
#define MAXA 100000
#define NCRIT 1
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXQ 20
#define MINA -100
#define MAXA 100
#define NL 1
#define NCRIT 3
#endif

const int RangeA = MAXA - MINA + 1;


int T;
int A[MAXN];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	int q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d %d\n", n, q);

	for (int i = 0; i < n; ++i)
		A[i] = rand() % RangeA + MINA;

	sort(A, A + n);
	for (int i = 0; i  < n; ++i) {
		if (i > 0) putchar(' ');
		printf("%d", A[i]);
	}
	putchar('\n');

	if (crit) {
		printf("1 %d\n", n);
		--q;
	}

	while (q--) {
		int i = rand() % n + 1;
		int j = rand() % n + 1;

		if (i > j) swap(i, j);
		printf("%d %d\n", i, j);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();
	puts("0");

	return 0;
}
