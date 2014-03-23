#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 30
#define MAXN 100
#define MAXC 5000
#define MAXW 1000
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXC 12
#define MAXW 1000
#define NL   1
#endif


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    printf("%d\n", n);

    int s, t, c;
    do {
        s = rand() % n + 1;
        t = rand() % n + 1;
    } while (s == t);
    c = crit ? MAXC : rand() % (MAXC + 1);

    printf("%d %d %d\n", s, t, c);

    while (c--) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;
        } while (u == v);
        int w = rand() % (MAXW + 1);
        printf("%d %d %d\n", u, v, w);
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
