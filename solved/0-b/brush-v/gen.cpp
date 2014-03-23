#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 100
#define MAXM 1000
#define MAXW 1000
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXM 16
#define MAXW 100
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int M = crit ? MAXM : rand() % (MAXM + 1);

    printf("\n%d %d\n", N, M);

    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v);

        int w = rand() % MAXW + 1;
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
