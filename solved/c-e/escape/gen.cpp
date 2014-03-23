#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 1
#define MAXT 210
#define MAXN 100
#endif

#if 0
#define MAXT 20
#define MAXN 8
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool vis[MAXN][MAXN];

void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    int MaxM = n*(n-1) / 2;
    int m = crit ? MaxM : rand() % (MaxM + 1);

    printf("\n%d %d\n", n, m);

    Zero(vis);
    while (m--) {
        int a, b;
        do {
            a = rand() % n;
            b = rand() % n;
        } while (a == b || vis[a][b]);

        vis[a][b] = vis[b][a] = true;
        printf("%d %d\n", a + 1, b + 1);
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
