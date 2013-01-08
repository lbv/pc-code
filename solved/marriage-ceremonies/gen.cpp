#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 100
#define MAXN 16
#define MAXV 10000
#define EXTRA_SPACES 0
#endif

#if 0
#define MAXT 20
#define MAXN 8
#define MAXV 100
#define EXTRA_SPACES 1
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;

#if EXTRA_SPACES
    puts("");
#endif
    printf("%d\n", N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", rand() % MAXV + 1);
        }
        putchar('\n');
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
