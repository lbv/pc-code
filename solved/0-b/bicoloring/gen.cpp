#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 200
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define NL   1
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool vis[MAXN][MAXN];


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int maxl = n * (n - 1) / 2;
    int l;

    do {
        l = crit ? maxl : rand() % maxl + 1;
        if (rand() % 20 == 0) l = n - 1;
    } while (l < n - 1);

#if NL
    puts("");
#endif
    printf("%d\n%d\n", n, l);

    Zero(vis);

    for (int i = 1; i < n; ++i) {
        int u = i;
        int v = rand() % i;

        vis[u][v] = vis[v][u] = true;
        printf("%d %d\n", u, v);
        --l;
    }

    while (l--) {
        int u, v;
        do {
            u = rand() % n;
            v = rand() % n;
        } while (u == v || vis[u][v]);

        vis[u][v] = vis[v][u] = true;
        printf("%d %d\n", u, v);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();

    puts("0");

    return 0;
}
