#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 100
#define MAXM 100000
#define MAXA 100000
#define MAXC 1000
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define MAXM 1000
#define MAXA 100
#define MAXC 50
#endif

#define Zero(v) memset((v), 0, sizeof(v))


int vis[MAXA + 1];


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    int m = rand() % (MAXM + 1);
    printf("%d %d\n", n, m);

    Zero(vis);
    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');

        int a;
        do {
            a = rand() % MAXA + 1;
        } while (vis[a]);
        vis[a] = true;
        printf("%d", a);
    }

    for (int i = 0; i < n; ++i) {
        int c = rand() % MAXC + 1;
        printf(" %d", c);
    }
    puts("");
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
