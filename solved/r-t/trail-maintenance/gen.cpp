#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 25
#define MAXN 200
#define MAXW 6000
#define MAXL 10000
#define EXTRA_NL 0
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXW 12
#define MAXL 100
#define EXTRA_NL 1
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int W = crit ? MAXW : rand() % MAXW + 1;

#if EXTRA_NL
    puts("");
#endif
    printf("%d %d\n", N, W);

    while (W--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v);
        int w = rand() % MAXL + 1;

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
