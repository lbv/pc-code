#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 100
#endif

#if 1
#define MAXT 20
#define MAXN 8
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool g[MAXN][MAXN];

void test_case(bool crit = false)
{
    int N = rand() % (MAXN - 1) + 2;
    if (crit) N = MAXN;
    printf("%d\n", N);

    int MaxR = N * (N - 1) / 2;
    int R;
    do {
        R = rand() % (MaxR + 1);
    } while (R < N - 1);
    printf("%d\n", R);

    Zero(g);

    for (int i = 1; i < N; ++i) {
        int u = rand() % i;
        int v = i;
        g[u][v] = g[v][u] = true;
        printf("%d %d\n", u, v);
        --R;
    }

    while (R--) {
        int u, v;
        do {
            u = rand() % N;
            v = rand() % N;
        } while (u == v || g[u][v]);

        g[u][v] = g[v][u] = true;
        printf("%d %d\n", u, v);
    }

    int s = rand() % N;
    int d = rand() % N;
    printf("%d %d\n", s, d);
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
