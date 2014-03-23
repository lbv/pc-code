#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 100
#define MAXP 1000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 5
#define MAXP 100
#define NL   1
#endif


#define Zero(v) memset((v), 0, sizeof(v))

bool used[MAXN + 1][MAXN + 1];
bool vis[MAXN + 1];

void test_case(bool crit = false)
{
#if NL
    puts("");
#endif
    int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
    printf("%d\n", N);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');

        int p = rand() % MAXP + 1;
        printf("%d", p);
    }
    puts("");

    int MaxM = N * (N-1) / 2;
    int M    = rand() % (MaxM + 1);
    printf("%d\n", M);

    Zero(used);
    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v || used[u][v]);
        used[u][v] = used[v][u] = true;

        int p = rand() % MAXP + 1;
        printf("%d %d %d\n", u, v, p);
    }

    int B, D;
    do {
        B = rand() % N + 1;
        D = rand() % N + 1;
    } while (B + D > N);
    printf("%d %d\n", B, D);

    Zero(vis);
    for (int i = 0; i < B; ++i) {
        if (i > 0) putchar(' ');

        int idx;
        do {
            idx = rand() % N + 1;
        } while (vis[idx]);
        vis[idx] = true;
        printf("%d", idx);
    }
    for (int i = 0; i < D; ++i) {
        int idx;
        do {
            idx = rand() % N + 1;
        } while (vis[idx]);
        vis[idx] = true;
        printf(" %d", idx);
    }
    puts("");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
