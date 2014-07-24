#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 30
#define MAXN 12
#define MAXK 1000000
#define MAXQ 1000
#define MAXR 100000000
#define NCRIT 3

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool used[MAXN];


void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
	int k = rand() % (MAXK + 1);
	int q = crit ? MAXQ : rand() % MAXQ + 1;

	printf("%d %d %d\n", n, k, q);
	for (int i = 0; i < n; ++i) {
		int t = rand() % n;
		Clr(used);
		used[i] = true;

		printf("%d", t);
		while (t--) {
			int v;
			do {
				v = rand() % n;
			} while (used[v]);
			used[v] = true;
			printf(" %d", v + 1);
		}
		putchar('\n');
	}

	while (q--) {
		int r = rand() % (MAXR + 1);
		printf("%d\n", r);
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
