#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))

#define MAXN 1000
#define MAXM 10000

#define MAXMONEY 1000

bool rel[MAXN + 1][MAXN + 1];

void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    int m = rand() % min(MAXM, n*(n-1)/2);

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; ++i) {
        int mon = rand() % MAXMONEY;
        printf("%s%d", i == 0 ? "" : " ", mon);
    }
    putchar('\n');

    Zero(rel);

    for (int i = 0; i < m; ++i) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;

            if (v < u) swap(u, v);
        } while (u == v || rel[u][v]);

        rel[u][v] = true;
        printf("%d %d\n", u, v);
    }
}

int main()
{
    srand(time(NULL));

    int T = 100;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}
