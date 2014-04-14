#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 15
#define MAXN 10000
#define MAXM 100000
#define MAXA 10000
#define MAXC 10000
#define EXTA_LINES 0
#endif

#if 0
#define MAXT 20
#define MAXN 10
#define MAXM 5
#define MAXA 100
#define MAXC 50
#define EXTRA_LINES 1
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int M = crit ? MAXM : rand() % MAXM + 1;
    int A = rand() % MAXA + 1;

#if EXTRA_LINES
    putchar('\n');
#endif

    printf("%d %d %d\n", N, M, A);

    while (M--) {
        int X, Y, C;
        do {
            X = rand() % N + 1;
            Y = rand() % N + 1;
        } while (X == Y);
        C = rand() % MAXC + 1;

        printf("%d %d %d\n", X, Y, C);
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
