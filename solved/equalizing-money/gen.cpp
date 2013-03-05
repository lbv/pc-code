#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT     100
#define MAXN     1000
#define MAXM     10000
#define MAXMONEY 1000
#define NL       0
#endif

#if 1
#define MAXT     20
#define MAXN     8
#define MAXM     12
#define MAXMONEY 100
#define NL       1
#endif


#define Zero(v) memset(v, 0, sizeof(v))

bool rel[MAXN + 1][MAXN + 1];

void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int m = crit ? MAXM : rand() % (min(MAXM, n*(n-1)/2) + 1);

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; ++i) {
        int mon = rand() % (MAXMONEY + 1);
        printf("%s%d", i == 0 ? "" : " ", mon);
    }
    putchar('\n');

    Zero(rel);

    for (int i = 0; i < m; ++i) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;
        } while (u == v || rel[u][v]);

        rel[u][v] = rel[v][u] = true;
        printf("%d %d\n", u, v);
    }
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
