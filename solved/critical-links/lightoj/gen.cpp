#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAXT 10
#define MAXN 1000
#define MAXE 100000

//#define MAXN 30
//#define MAXE 100

#define Zero(v) memset(v, 0, sizeof(v))

bool g[MAXN][MAXN];

void test_case()
{
    Zero(g);
    int n = rand() % (MAXN + 1);

    printf("\n%d\n", n);
    if (n == 0) return;

    int e = rand() % MAXE;
    while (e--) {
        if (n == 1) break;

        int u, v;
        do {
            u = rand() % n;
            v = rand() % n;
        } while (u == v);

        g[u][v] = true;
        g[v][u] = true;
    }

    for (int i = 0; i < n; ++i) {
        int ne = 0;
        for (int j = 0; j < n; ++j)
            if (g[i][j]) ++ne;

        printf("%d (%d)", i, ne);
        for (int j = 0; j < n; ++j)
            if (g[i][j]) printf(" %d", j);
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
