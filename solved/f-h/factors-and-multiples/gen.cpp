#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 100
#define MAXM 100
#endif

#if 1
#define MAXT 500
#define MAXN 100
#define MAXM 100
#endif


int T;

int ns[MAXN];


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d", n);
	for (int i = 0; i < n; ++i) {
		ns[i] = rand() % 10000;
		printf(" %d", ns[i]);
	}
	puts("");

	int m = crit ? MAXM : rand() % MAXM + 1;
	printf("%d", m);
	for (int i = 0; i < m; ++i) {
		int elem = 0;
		if (rand() % 3 < 2) {
			int idx = rand() % n;
			elem = ns[idx] * (rand() % 1000 + 1);
		}
		else
			elem = rand() % 1000000;
		printf(" %d", elem);
	}
	puts("");

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < 5; ++i) test_case(true);

	while (T) test_case();

	return 0;
}
