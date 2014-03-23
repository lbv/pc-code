#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXN 2000
#define MAXV 1000000000
#endif

#if 1
#define MAXT 20
#define MAXN 15
#define MAXV 100000
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % (MAXN - 2) + 3;
    printf("%d\n", N);
    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand() % MAXV + 1);
    }
    putchar('\n');
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
