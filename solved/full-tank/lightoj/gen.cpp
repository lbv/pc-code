#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 5
#define MAXN 100
#define MAXM 1000
#define MAXF 100
#define MAXC 100
#define MAXW 100
#define MAXQ 100


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int m = crit ? MAXM : rand() % (MAXM + 1);

    printf("%d %d\n", n, m);

    printf("%d", rand() % MAXF + 1);
    for (int i = 1; i < n; ++i)
        printf(" %d", rand() % MAXF + 1);
    putchar('\n');

    while (m--) {
        int u, v;
        do {
            u = rand() % n;
            v = rand() % n;
        } while (u == v);

        int w = rand() % MAXW + 1;
        printf("%d %d %d\n", u, v, w);
    }

    int q = rand() % MAXQ + 1;
    printf("%d\n", q);
    while (q--) {
        int c = rand() % MAXC + 1;
        int s = rand() % n;
        int t = rand() % n;
        printf("%d %d %d\n", c, s, t);
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
