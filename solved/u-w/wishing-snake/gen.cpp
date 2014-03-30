#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 65
#define MAXN 100
#define MAXK 100
#define MAXCP 1000
#endif

#if 1
#define MAXT 20
#define MAXN 1
#define MAXK 12
#define MAXCP 5
#define NL 1
#endif


#define Zero(v) memset(v, 0, sizeof(v))


bool rel[MAXCP][MAXCP];
int T;


void test_case()
{
#if NL
	puts("");
#endif

	Zero(rel);

	int n = rand() % MAXN + 1;
	printf("%d\n", n);

	for (int i = 0; i < n; ++i) {
		int k = rand() % MAXK + 1;
		printf("%d\n", k);

		for (int j = 0; j < k; ++j) {
			int u, v;
			do {
				u = rand() % MAXCP;
				v = rand() % MAXCP;
			} while (u == v || rel[u][v]);

			rel[u][v] = true;
			printf("%d %d\n", u, v);
		}
	}
	--T;
}

void test_good()
{
#if NL
	puts("");
#endif
	Zero(rel);

	int n = rand() % MAXN + 1;
	printf("%d\n", n);

	int u = 0;

	for (int i = 0; i < n; ++i) {
		int k = rand() % MAXK + 1;
		printf("%d\n", k);

		for (int j = 0; j < k; ++j) {
			int v;
			do {
				v = rand() % MAXCP;
			} while (u == v || rel[u][v]);

			rel[u][v] = true;
			printf("%d %d\n", u, v);
			u = v;
		}
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) {
		int r = rand() % 10;
		if (r < 6) test_good();
		else test_case();
	}

	return 0;
}
