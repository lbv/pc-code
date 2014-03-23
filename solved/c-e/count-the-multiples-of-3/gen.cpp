#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define USE_EXTRA_SPACES 0
#endif

#if 0
#define MAXT 10
#define MAXN 50
#define MAXQ 8
#define USE_EXTRA_SPACES 1
#endif


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    int q = crit ? MAXQ : rand() % MAXQ + 1;

#if USE_EXTRA_SPACES
    putchar('\n');
#endif

    printf("%d %d\n", n, q);

    for (int i = 1; i < q; ++i) {
        int j = rand() % n;
        int i = rand() % (j + 1);
        int op = rand() % 2;

        printf("%d %d %d\n", op, i, j);
    }
    printf("1 0 %d\n", n-1);
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
